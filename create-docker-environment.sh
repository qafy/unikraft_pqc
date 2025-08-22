#!/usr/bin/env bash

CONTAINER_NAME="uk-build-epqciuoe-$(whoami)"
CONTEXT=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )


if docker inspect --format '{{.State.Running}}' "$CONTAINER_NAME" 1>/dev/null 2>/dev/null; then
    echo "Attaching to existing container: $CONTAINER_NAME"
    docker exec -it $CONTAINER_NAME bash
else
    echo "Starting new container: $CONTAINER_NAME"
    docker build -t uk-build-epqciuoe -f ./Unikraft/uk-build-aarch64 . 
    # 2>/dev/null
    docker run \
        --hostname uk-build \
        --name $CONTAINER_NAME \
        -it --rm --privileged \
        -v /var/run/docker.sock:/var/run/docker.sock \
        -v $(pwd):/workspace \
        -e OUTER_MOUNT_PATH=$(pwd) \
        uk-build-epqciuoe 

fi




