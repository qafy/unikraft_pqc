#!/usr/bin/env bash

SCRIPT_PATH=$(realpath "$0")
SCRIPT_DIR=$(dirname "$SCRIPT_PATH")

VOPENSSL="3.4.1"
VLIBOQS="0.12.0"
VOQS_PROVIDER="0.8.0"

# The local install directory path needs to be absolute because openssl has no way to allow relative paths
# This is the reason the path is specified here for our target machine
CONTAINER_INSTALL_DIR="/workspace/Native/local"
DEVICE_INSTALL_DIR="/home/user/Desktop/epqciuoe/Native/local"

function setup_openssl()
{   
    git clone --depth 1 --branch openssl-${VOPENSSL} https://github.com/openssl/openssl.git src/openssl
    mkdir local/openssldir
    mkdir build
    cd src/openssl

    ./Configure \
		--prefix="$1" \
		--openssldir="$1/openssldir" \
		--with-rand-seed=getrandom \
        '-Wl,-rpath,$(LIBRPATH)' \
        no-shared \
        no-tests \
		no-async \
		no-docs \
		no-zlib \
		no-async \
		no-comp \
		no-idea \
		no-mdc2 \
		no-rc5 \
		no-ec2m \
		no-ssl3 \
		no-seed \
        no-weak-ssl-ciphers && \
    make -j$(nproc) && \
    make install
}

function setup_liboqs()
{
    git clone --depth 1 --branch ${VLIBOQS} https://github.com/open-quantum-safe/liboqs.git src/liboqs
    cd src/liboqs

    mkdir build
    cd build
    cmake .. \
        -DCMAKE_INSTALL_PREFIX="$1" \
        -DOPENSSL_ROOT_DIR="$1/openssl"
    make -j$(nproc)
    make install
    
    cd ..
    rm -rf build
}

function setup_oqs_provider()
{
    git clone --depth 1 --branch ${VOQS_PROVIDER} https://github.com/open-quantum-safe/oqs-provider.git src/oqsprovider
    cd src/oqsprovider
    
    export liboqs_DIR="$1"
    export OPENSSL_INSTALL="$1"
    export CMAKE_PARAMS="-DCMAKE_INSTALL_PREFIX=$1"
    ./scripts/fullbuild.sh
    cd _build 
    make install
    cd ..
    rm -rf _build
}

function make_local_install()
{
    mkdir local
    mkdir src
}

function make_oqs_speed()
{
    cd oqs_speed
    make
}

function clean_local_install()
{
    rm -rf local
    rm -rf src
    rm -rf build

    rm openssl
    rm benchmark
    cd oqs_speed
    make clean
}


function main()
{   
    cd $SCRIPT_DIR
    if [ "$1" == "clean" ]; then
        echo "Removing local files"
        clean_local_install
        exit
    fi

    if [ "$1" == "install" ]; then
        echo "Installing on device"
        mkdir -p $DEVICE_INSTALL_DIR
        cp -r $SCRIPT_DIR/build/local/* $DEVICE_INSTALL_DIR
        exit
    fi
    # Install the the libraries for the container environment
    cd $SCRIPT_DIR
    make_local_install 
    cd $SCRIPT_DIR
    setup_openssl $CONTAINER_INSTALL_DIR
    cd $SCRIPT_DIR
    setup_liboqs $CONTAINER_INSTALL_DIR
    cd $SCRIPT_DIR
    setup_oqs_provider $CONTAINER_INSTALL_DIR
    cd $SCRIPT_DIR
    make_oqs_speed
    cp $SCRIPT_DIR/openssl.cnf $CONTAINER_INSTALL_DIR/openssldir

    # Build the libraries for the device
    mkdir -p $DEVICE_INSTALL_DIR
    cd $SCRIPT_DIR
    setup_openssl $DEVICE_INSTALL_DIR
    cd $SCRIPT_DIR
    setup_liboqs $DEVICE_INSTALL_DIR
    cd $SCRIPT_DIR
    setup_oqs_provider $DEVICE_INSTALL_DIR
    cd $SCRIPT_DIR
    cp $SCRIPT_DIR/openssl.cnf $DEVICE_INSTALL_DIR/openssldir
    cp -r $DEVICE_INSTALL_DIR $SCRIPT_DIR/build

cat << EOF > $SCRIPT_DIR/openssl
#!/usr/bin/env bash
SCRIPT_PATH=\$(realpath "\$0")
SCRIPT_DIR=\$(dirname "\$SCRIPT_PATH")

\$SCRIPT_DIR/local/bin/openssl \$*
EOF

cat << EOF > $SCRIPT_DIR/benchmark
#!/usr/bin/env bash
SCRIPT_PATH=\$(realpath "\$0")
SCRIPT_DIR=\$(dirname "\$SCRIPT_PATH")

\$SCRIPT_DIR/oqs_speed/benchmark \$*
EOF

    chmod +x $SCRIPT_DIR/openssl
    chmod +x $SCRIPT_DIR/benchmark

    echo "Setup complete"
}

main $@