#!/usr/bin/env bash

SCRIPT_PATH=$(realpath "$0")
SCRIPT_DIR=$(dirname "$SCRIPT_PATH")

if [ "$1" == "clean" ]; then
    docker network rm alpine-bench-net 2>/dev/null
    docker image rm alpine-bench 2>/dev/null
    rm $SCRIPT_DIR/openssl
    exit
fi  

docker network create -d bridge alpine-bench-net
docker build -t alpine-bench -f ./Container/alpine-bench-aarch64 $SCRIPT_DIR

cat << EOF > $SCRIPT_DIR/openssl
#!/usr/bin/env bash
docker run \\
    --name alpine_bench_\$(whoami) \\
    --network=alpine-bench-net \\
    -v \$(pwd):/workspace \\
    -it --rm \\
    -p 442:442 \\
    --add-host host.docker.internal=host-gateway \\
    alpine-bench \\
    openssl \$*
EOF

cat << EOF > $SCRIPT_DIR/sh
#!/usr/bin/env bash
docker run \\
    --name alpine_bench_\$(whoami) \\
    --network=alpine-bench-net \\
    -v \$(pwd):/workspace \\
    -it --rm \\
    -p 442:442 \\
    --add-host host.docker.internal=host-gateway \\
    alpine-bench \\
    sh
EOF

chmod a+x $SCRIPT_DIR/openssl
chmod a+x $SCRIPT_DIR/sh