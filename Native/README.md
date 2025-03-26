- What is FIPS, is it important?
- Reduce the ./Configure script from openssl so that teh Makefile gets as small as possible
- Inspect build system of unikraft to understand how to write a custom Makefile
- liboqs has configuration that can enable hardware acceleration OQS_USE_CPUFEATURE_INSTRUCTIONS
- maybe we can use elfloader for this and do not even need to port the library
- OQS_EMBEDDED_BUILD can be used to omit use of filesystem + systemcalls
- liboqss ninja run_tests does not pass all tests on this version on this mac
- liboqs may need static
https://github.com/open-quantum-safe/oqs-provider/blob/main/examples/static_oqsprovider.c

# Used Sources for Information

# Dependencies
- openssl-3.4.1
- liboqs-0.12.0
- oqs-provider-0.8.0

## Configuration for openssl
./Configure --prefix=/Users/moritzbeckel/Desktop/IDP/src/opt --openssldir=/Users/moritzbeckel/Desktop/IDP/src/usr/local
pip3 install --break-system-packages pytest pytest-xdist pyyaml

## Configuration for liboqs
mkdir build && cd build
cmake -GNinja .. -DOQS_USE_OPENSSL=OFF -DCMAKE_INSTALL_PREFIX=/Users/moritzbeckel/Desktop/IDP/src/opt
ninja

## Configuration for oqs-provider
export liboqs_DIR="/Users/moritzbeckel/Desktop/IDP/src/opt"
export OPENSSL_INSTALL="/Users/moritzbeckel/Desktop/IDP/src/opt"
export CMAKE_PARAMS="-DOQS_PROVIDER_BUILD_STATIC=ON -DCMAKE_INSTALL_PREFIX=/Users/moritzbeckel/Desktop/IDP/src/opt"
./scripts/fullbuild.sh
cmake --install _build

## Example demo-oqsprovider
- Make sure that no dynamic libraries are present (rename .so/.dylib files)
- check with otool -L that no dynamic libraries are used
