#!/usr/bin/env bash

scp ./Unikraft/ssl_uk/build/ssl_uk_qemu-arm64 \
    user@172.21.21.1:/home/user/Desktop/

ssh user@172.21.21.1 \
    'qemu-system-aarch64 -enable-kvm -kernel Desktop/ssl_uk_qemu-arm64 -machine virt -cpu max -m 128M -nographic'


# Debugging

# qemu-system-aarch64 \
#                 -enable-kvm \
#                 -kernel Desktop/ssl_uk_qemu-arm64 \
#                 -machine virt -cpu max -m 128M \
#                 -nographic -no-acpi -display none \
#                 -append verbose 

# gdb --eval-command="target remote 172.21.21.1:1234" \
#     build/ssl_uk_qemu-arm64.dbg