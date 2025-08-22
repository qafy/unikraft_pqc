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

qemu-system-aarch64 \\
    -enable-kvm \\
	-kernel \$SCRIPT_DIR/ssl_uk_bin/build/ssl_uk_qemu-arm64 \\
	-machine virt -cpu max -m 128M \\
	-nographic \\
	-netdev bridge,id=en0,br=virbr0 \\
    -device virtio-net-pci,netdev=en0 \\
	-append "ssl_uk netdev.ip=172.44.0.2/24:172.44.0.1::: vfs.fstab=[ \"fs0:/:9pfs:::\" ] -- \$*" \\
    -fsdev local,id=myid,path=\$(pwd),security_model=none \\
    -device virtio-9p-pci,fsdev=myid,mount_tag=fs0
EOF

chmod a+x $SCRIPT_DIR/openssl

cat << EOF > $SCRIPT_DIR/test
#!/usr/bin/env bash
SCRIPT_PATH=\$(realpath "\$0")
SCRIPT_DIR=\$(dirname "\$SCRIPT_PATH")

qemu-system-aarch64 \\
    -kernel \$SCRIPT_DIR/ssl_uk_test/build/ssl_uk_qemu-arm64 \\
    -machine virt -cpu max -m 128M \\
    -nographic
EOF

chmod a+x $SCRIPT_DIR/test


cat << EOF > $SCRIPT_DIR/benchmark
#!/usr/bin/env bash
SCRIPT_PATH=\$(realpath "\$0")
SCRIPT_DIR=\$(dirname "\$SCRIPT_PATH")
SEED=\$(hexdump -vn32 -e'8/4 "0x%08X "' /dev/urandom)
qemu-system-aarch64 \\
    -enable-kvm \\
    -append "ssl_uk random.seed=[\${SEED}] -- \$*" \\
    -kernel \$SCRIPT_DIR/oqs_uk_speed/build/ssl_uk_qemu-arm64 \\
    -append " -- \$*" \\
    -machine virt -cpu max -m 1G \\
    -nographic
EOF

chmod a+x $SCRIPT_DIR/benchmark


