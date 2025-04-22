#!/usr/bin/env bash

SCRIPT_PATH=$(realpath "$0")
SCRIPT_DIR=$(dirname "$SCRIPT_PATH")

VOPENSSL="3.4.1"
VLIBOQS="0.12.0"
VOQS_PROVIDER="0.8.0"

function setup_openssl()
{
    git clone --depth 1 --branch openssl-${VOPENSSL} https://github.com/openssl/openssl.git src/openssl
    mkdir local/openssldir
    cd src/openssl

    ./Configure \
		--prefix=${SCRIPT_DIR}/local \
		--openssldir=${SCRIPT_DIR}/local/openssldir \
		--with-rand-seed=getrandom \
        '-Wl,-rpath,$(LIBRPATH)' \
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
		no-weak-ssl-ciphers
    
    make -j$(nproc)
    make install

}

function setup_liboqs()
{
    git clone --depth 1 --branch ${VLIBOQS} https://github.com/open-quantum-safe/liboqs.git src/liboqs
    cd src/liboqs

    mkdir build && cd build
    export CMAKE_INSTALL_PREFIX="${SCRIPT_DIR}/local"
    export OPENSSL_ROOT_DIR="${SCRIPT_DIR}/src/openssl"
    cmake ..
    cmake --build . -- -j$(nproc)
    cmake --install .

}

function setup_oqs_provider()
{
    git clone --depth 1 --branch ${VOQS_PROVIDER} https://github.com/open-quantum-safe/oqs-provider.git src/oqsprovider
    cd src/oqsprovider
    
    export liboqs_DIR="${SCRIPT_DIR}/local"
    export OPENSSL_INSTALL="${SCRIPT_DIR}/local"
    export CMAKE_PARAMS="-DCMAKE_INSTALL_PREFIX=${SCRIPT_DIR}/local"
    ./scripts/fullbuild.sh
    cmake --install _build
}

function make_local_install()
{
    rm -rf local
    mkdir local
    rm -rf src
    mkdir src
    rm openssl 2>/dev/null
}

function clean_local_install()
{
    rm -rf local
    rm -rf src
    rm openssl 2>/dev/null
}
# Dependencies: astyle cmake gcc ninja-build libssl-dev python3-pytest python3-pytest-xdist unzip xsltproc doxygen graphviz python3-yaml valgrind
function main()
{   
    cd $SCRIPT_DIR
    if [ "$1" == "clean" ]; then
        echo "Removing local files"
        clean_local_install
        exit
    fi

    cd $SCRIPT_DIR
    make_local_install
    cd $SCRIPT_DIR
    setup_openssl
    cd $SCRIPT_DIR
    setup_liboqs
    cd $SCRIPT_DIR
    setup_oqs_provider

    ln -s $SCRIPT_DIR/local/bin/openssl $SCRIPT_DIR/openssl
    cp $SCRIPT_DIR/openssl.cnf $SCRIPT_DIR/local/openssldir/openssl.cnf
}

main $@