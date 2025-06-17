#!/usr/bin/env bash

CONTAINER_NAME="uk-build-$(whoami)"
CONTEXT=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

function run_docker()
{
    if docker inspect --format '{{.State.Running}}' "$CONTAINER_NAME" 1>/dev/null 2>/dev/null; then
        echo "Attaching to existing container: $CONTAINER_NAME"
        docker exec -it $CONTAINER_NAME bash
    else
        echo "Starting new container: $CONTAINER_NAME"
        docker build -t uk-build -f ./Unikraft/uk-build-aarch64 . 
        # 2>/dev/null
        docker run \
            --hostname uk-build \
            --name $CONTAINER_NAME \
            -it --rm --privileged \
            -v /var/run/docker.sock:/var/run/docker.sock \
            -v $(pwd):/workspace \
            uk-build 

    fi
}


# function run_docker()
# {
#     if docker inspect --format '{{.State.Running}}' "$CONTAINER_NAME" 1>/dev/null 2>/dev/null; then
#         echo "Attaching to existing container: $CONTAINER_NAME"
#         docker exec -it $CONTAINER_NAME bash
#     else
#         echo "Starting new container: $CONTAINER_NAME"
#         docker build -t kraft-build \
#         -f ./container-files/kraft-aarch64 \
#         --build-arg USER=${USER} \
#         --build-arg UID=$(id -u) \
#         --build-arg GID=1001 \
#         ./container-files
#         # 2>/dev/null
#         docker run --name $CONTAINER_NAME \
#         -it --rm --privileged \
#         -v $(pwd):/workspace \
#         --env="DISPLAY" \
#         --network host \
#         kraft-build
#     fi
# }

run_docker
