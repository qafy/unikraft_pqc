#!/usr/bin/env bash

SCRIPT_PATH=$(realpath "$0")
SCRIPT_DIR=$(dirname "$SCRIPT_PATH")
FOLDER_NAME=$(basename $SCRIPT_DIR)

USER=user
IP=172.21.21.1

rsync -avz  --exclude='.git' --exclude='.vscode' --exclude='.DS_Store' \
            --exclude="*.d" --exclude="*.o" --exclude="*.o.cmd" \
            --exclude="Native/local" \
            $SCRIPT_DIR $USER@$IP:/home/$USER/Desktop/

# Install the container and the openssl library on the device
ssh $USER@$IP "/home/$USER/Desktop/epqciuoe/Container/setup.sh install"
ssh $USER@$IP "/home/$USER/Desktop/epqciuoe/Native/setup.sh install"

ssh -t $USER@$IP "cd /home/$USER/Desktop/$FOLDER_NAME; bash --login"

# Debugging
#
# qemu-system-aarch64 \
#                 -s -S \
#                 -kernel build/ssl_uk_qemu-arm64 \
#                 -machine virt -cpu max -m 128M \
#                 -nographic -no-acpi -display none \
#                 -append verbose 
#
# gdb --eval-command="target remote 172.21.21.1:1234" \
#     build/ssl_uk_qemu-arm64.dbg