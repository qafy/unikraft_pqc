#!/usr/bin/env bash

SCRIPT_PATH=$(realpath "$0")
SCRIPT_DIR=$(dirname "$SCRIPT_PATH")

if [ "$1" == "clean" ]; then
    docker network rm alpine-bench-net 2>/dev/null
    docker image rm alpine-bench-epqciuoe 2>/dev/null
    rm $SCRIPT_DIR/oqs_speed/benchmark
    rm $SCRIPT_DIR/alpine_bench.tar
    rm $SCRIPT_DIR/openssl
    rm $SCRIPT_DIR/sh
    rm $SCRIPT_DIR/benchmark
    exit
fi  

if [ "$1" == "install" ]; then 
    docker load -i $SCRIPT_DIR/alpine_bench.tar
    exit
fi

docker network create -d bridge alpine-bench-net
docker build --platform linux/arm64 -t alpine-bench-epqciuoe -f $SCRIPT_DIR/alpine-bench-aarch64 $SCRIPT_DIR

docker create --name temp-container alpine-bench-epqciuoe 
docker cp temp-container:/local/oqs_speed/benchmark $SCRIPT_DIR/oqs_speed/benchmark
docker rm temp-container

docker save -o $SCRIPT_DIR/alpine_bench.tar alpine-bench-epqciuoe

cat << EOF > $SCRIPT_DIR/openssl
#!/usr/bin/env bash
if [ -z "\${OUTER_MOUNT_PATH}" ]; then
    OUTER_MOUNT_PATH=\$(pwd)
fi
if [ "\$1" == "pid" ]; then
    docker run \
    --network=alpine-bench-net \
    -v \$OUTER_MOUNT_PATH:/workspace --rm \
    -p 442:442 \
    --add-host host.docker.internal=host-gateway \
    alpine-bench-epqciuoe \
    openssl "\${@:2}" 1>/dev/null&
    echo \$!
    exit
fi
docker run \\
    --name alpine_bench_\$(whoami) \\
    --network=alpine-bench-net \\
    -v \$OUTER_MOUNT_PATH:/workspace \
    -it --rm \\
    -p 442:442 \\
    --add-host host.docker.internal=host-gateway \\
    alpine-bench-epqciuoe \\
    openssl \$*
EOF

cat << EOF > $SCRIPT_DIR/sh
#!/usr/bin/env bash
if [ -z "\${OUTER_MOUNT_PATH}" ]; then
    OUTER_MOUNT_PATH=\$(pwd)
fi
docker run \\
    --name alpine_bench_\$(whoami) \\
    --network=alpine-bench-net \\
    -v \$OUTER_MOUNT_PATH:/workspace \
    -it --rm \\
    -p 442:442 \\
    --add-host host.docker.internal=host-gateway \\
    alpine-bench-epqciuoe \\
    sh
EOF

cat << EOF > $SCRIPT_DIR/benchmark
#!/usr/bin/env bash
if [ "\$1" == "pid" ]; then
    docker run \
    --network=alpine-bench-net \
    --rm \
    alpine-bench-epqciuoe \
    /local/oqs_speed/benchmark "\${@:2}" 1>/dev/null&
    echo \$!
    exit
fi
docker run \\
    --name alpine_bench_\$(whoami) \\
    --network=alpine-bench-net \\
    -it --rm \\
    alpine-bench-epqciuoe \\
    /local/oqs_speed/benchmark \$*
EOF

chmod a+x $SCRIPT_DIR/openssl
chmod a+x $SCRIPT_DIR/sh
chmod a+x $SCRIPT_DIR/benchmark