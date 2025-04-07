#!/usr/bin/env bash

scp ./Unikraft/ssl_uk/build/ssl_uk_qemu-arm64 \
    user@172.21.21.1:/home/user/Desktop/

ssh user@172.21.21.1 \
    'cd Desktop; qemu-system-aarch64 -kernel ssl_uk_qemu-arm64 -machine virt -cpu max -m 64M -nographic'