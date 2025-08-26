#!/usr/bin/env bash

SCRIPT_PATH=$(realpath "$0")
SCRIPT_DIR=$(dirname "$SCRIPT_PATH")

if [ "$1" == "clean" ]; then
    docker network rm alpine-bench-net 2>/dev/null
    docker image rm alpine-bench-epqciuoe 2>/dev/null
    rm $SCRIPT_DIR/alpine_bench.tar
    rm $SCRIPT_DIR/openssl
    rm $SCRIPT_DIR/sh
    rm $SCRIPT_DIR/benchmark
    exit
fi  

if [ "$1" == "install" ]; then 
    docker
    docker load -i $SCRIPT_DIR/alpine_bench.tar
    exit
fi

docker network create -d bridge alpine-bench-net
docker build --platform linux/arm64 -t alpine-bench-epqciuoe -f $SCRIPT_DIR/alpine-bench-aarch64 $SCRIPT_DIR
docker save -o $SCRIPT_DIR/alpine_bench.tar alpine-bench-epqciuoe

cat << EOF > $SCRIPT_DIR/openssl
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