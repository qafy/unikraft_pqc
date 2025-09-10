#!/usr/bin/env bash

SCRIPT_PATH=$(realpath "$0")
SCRIPT_DIR=$(dirname "$SCRIPT_PATH")

if [ "$1" == "clean" ]; then    
    ip link del dev virbr0 type bridge 2>/dev/null
    rm $SCRIPT_DIR/openssl
    rm $SCRIPT_DIR/test
    rm $SCRIPT_DIR/benchmark
    rm -rf $SCRIPT_DIR/ssl_uk_test/build
    rm -rf $SCRIPT_DIR/ssl_uk_bin/build
    rm -rf $SCRIPT_DIR/oqs_uk_speed/build
    exit
fi  

ip link add dev virbr0 type bridge
ip address add 172.44.0.1/24 dev virbr0
ip link set dev virbr0 up

cd $SCRIPT_DIR/ssl_uk_bin
make -j$(nproc)
cd ..
cd $SCRIPT_DIR/ssl_uk_test
make -j$(nproc)
cd ..
cd $SCRIPT_DIR/oqs_uk_speed
make -j$(nproc)
cd ..

cat << EOF > $SCRIPT_DIR/openssl
#!/usr/bin/env bash
SCRIPT_PATH=\$(realpath "\$0")
SCRIPT_DIR=\$(dirname "\$SCRIPT_PATH")
if [ -e "/dev/kvm" ]; then
    KVM_SUPPORT="-enable-kvm"
fi
SEED=\$(hexdump -vn32 -e'8/4 "0x%08X "' /dev/urandom)
if [ "\$1" == "pid" ]; then
    qemu-system-aarch64 \
	-kernel \$SCRIPT_DIR/ssl_uk_bin/build/ssl_uk_qemu-arm64 \
	-machine virt -cpu max -m 128M \
	-nographic \
	-netdev bridge,id=en0,br=virbr0 \
    -device virtio-net-pci,netdev=en0 \
	-append "ssl_uk random.seed=[\${SEED}] netdev.ip=172.44.0.2/24:172.44.0.1::: vfs.fstab=[ \"fs0:/:9pfs:::\" ] -- \${*:2}" \
    -fsdev local,id=myid,path=\$(pwd),security_model=none \
    -device virtio-9p-pci,fsdev=myid,mount_tag=fs0 \
    \$KVM_SUPPORT 1>/dev/null &
    echo \$!
    exit
fi
qemu-system-aarch64 \\
	-kernel \$SCRIPT_DIR/ssl_uk_bin/build/ssl_uk_qemu-arm64 \\
	-machine virt -cpu max -m 128M \\
	-nographic \\
	-netdev bridge,id=en0,br=virbr0 \\
    -device virtio-net-pci,netdev=en0 \\
	-append "ssl_uk random.seed=[\${SEED}] netdev.ip=172.44.0.2/24:172.44.0.1::: vfs.fstab=[ \"fs0:/:9pfs:::\" ] -- \$*" \\
    -fsdev local,id=myid,path=\$(pwd),security_model=none \\
    -device virtio-9p-pci,fsdev=myid,mount_tag=fs0 \\
    \$KVM_SUPPORT
EOF

cat << EOF > $SCRIPT_DIR/test
#!/usr/bin/env bash
SCRIPT_PATH=\$(realpath "\$0")
SCRIPT_DIR=\$(dirname "\$SCRIPT_PATH")

qemu-system-aarch64 \\
    -kernel \$SCRIPT_DIR/ssl_uk_test/build/ssl_uk_qemu-arm64 \\
    -machine virt -cpu max -m 128M \\
    -nographic
EOF

cat << EOF > $SCRIPT_DIR/benchmark
#!/usr/bin/env bash
SCRIPT_PATH=\$(realpath "\$0")
SCRIPT_DIR=\$(dirname "\$SCRIPT_PATH")
if [ -e "/dev/kvm" ]; then
    KVM_SUPPORT="-enable-kvm"
fi
SEED=\$(hexdump -vn32 -e'8/4 "0x%08X "' /dev/urandom)
if [ "\$1" == "pid" ]; then
    qemu-system-aarch64 \
    -append "ssl_uk random.seed=[\${SEED}] -- \${*:2}" \
    -kernel \$SCRIPT_DIR/oqs_uk_speed/build/ssl_uk_qemu-arm64 \
    -machine virt -cpu max -m 1G \
    -nographic \
    \$KVM_SUPPORT 1>/dev/null &
    echo \$!
    exit
fi
qemu-system-aarch64 \\
    -append "ssl_uk random.seed=[\${SEED}] -- \$*" \\
    -kernel \$SCRIPT_DIR/oqs_uk_speed/build/ssl_uk_qemu-arm64 \\
    -machine virt -cpu max -m 1G \\
    -nographic \\
    \$KVM_SUPPORT
EOF


chmod a+x $SCRIPT_DIR/test
chmod a+x $SCRIPT_DIR/openssl
chmod a+x $SCRIPT_DIR/benchmark


