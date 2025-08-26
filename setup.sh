#!/usr/bin/env bash

SCRIPT_PATH=$(realpath "$0")
SCRIPT_DIR=$(dirname "$SCRIPT_PATH")

if [ "$1" == "clean" ]; then    
    $SCRIPT_DIR/Native/setup.sh clean
    $SCRIPT_DIR/Unikraft/setup.sh clean
    $SCRIPT_DIR/Container/setup.sh clean
    exit
fi  

CONTAINER_NAME="uk-setup-epqciuoe-$(whoami)"

echo "Bulding setup container: $CONTAINER_NAME"
docker build --platform linux/arm64 -t uk-build-epqciuoe -f ./Unikraft/uk-build-aarch64 . 

echo "Starting setup container: $CONTAINER_NAME"

docker run \
    --hostname uk-build \
    --name $CONTAINER_NAME \
    -it --rm --privileged \
    -v /var/run/docker.sock:/var/run/docker.sock \
    -v $(pwd):/workspace \
    -e OUTER_MOUNT_PATH=$(pwd) \
    --entrypoint /workspace/Native/setup.sh \
    uk-build-epqciuoe 

$SCRIPT_DIR/Container/setup.sh

docker run \
    --hostname uk-build \
    --name $CONTAINER_NAME \
    -it --rm --privileged \
    -v /var/run/docker.sock:/var/run/docker.sock \
    -v $(pwd):/workspace \
    -e OUTER_MOUNT_PATH=$(pwd) \
    --entrypoint /workspace/Unikraft/setup.sh \
    uk-build-epqciuoe