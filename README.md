# Dependencies
- openssl-3.4.1
- liboqs-0.12.0
- oqs-provider-0.8.0

## Configuration for openssl
./Configure CC=/workspace/musl-install/bin/musl-gcc LD=/workspace/musl-install/syslibdir/ld-musl-aarch64.so.1 --prefix=/workspace/Native/opt --openssldir=/workspace/Native/usr/local --with-rand-seed=getrandom no-async no-apps no-docs no-tests no-async \
	    no-shared \
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


- What is FIPS, is it important?
- Reduce the ./Configure script from openssl so that teh Makefile gets as small as possible
- Inspect build system of unikraft to understand how to write a custom Makefile
- liboqs has configuration that can enable hardware acceleration OQS_USE_CPUFEATURE_INSTRUCTIONS
- maybe we can use elfloader for this and do not even need to port the library
- OQS_EMBEDDED_BUILD can be used to omit use of filesystem + systemcalls
- liboqss ninja run_tests does not pass all tests on this version on this mac
- liboqs may need static
https://github.com/open-quantum-safe/oqs-provider/blob/main/examples/static_oqsprovider.c

- TODO openssl compiler uses gcc -> we need to set compiler prefix to make sure it uses arm compilation even on x86 container
- TODO dependencies for musl linux-headers curl gcc + the kraft dependencies
- TODO (option for me) write gdb init that make gdb easier to use (set pagination off, ctrl c default3)

- enabled sigsetjmp in the Makefile.signal rule in libmusl TODO look into why this does not work
- compiled openssl inside alpine linux with musl instead of glibc TODO find a way to do this without docker 
- Dependencies (Alpine): linux-headers perl curl gcc make 

- TODO create patch libmusl needs to be patched in Makefile rules signal ifeq aarch64 -> arm64 
- TODO check for __attribute__((constructor)) to see library intizializes something and causes the crash
- TODO check for sigsetjmp that this may cause the crash
- cannot get signals to work properly look into that
- https://github.com/unikraft/unikraft/pull/1461 says that irqs need to be enabled 
- https://unikraft.org/docs/internals/booting

- guess that it is a constructor was right
- it is OPENSSL_cpuid_setup
- assumption construtor has (void) as argument, maybe because unikraft passes arguments to it it does not work
- not its not the problem
- found this https://gitlab.alpinelinux.org/alpine/aports/-/blob/master/main/openssl/auxv.patch
- says openssl intentionally executes invalid instruction sigill

cd /workspace/Native/openssl-openssl-3.4.1/crypto
patch < /workspace/auxv.patch 

./configure --prefix=/workspace/musl-install/ --syslibdir=/workspace/musl-install/syslibdir/ 
https://mirrors.edge.kernel.org/pub/linux/kernel/v6.x/linux-6.12.6.tar.xz
make headers ARCH="arm64"
- copy usr/include into musl-insall/include

Configure musl-gcc path with CC= in openssl configuration script

Compilation will fail but the libcrypto is produced still have to look at a fix for this

- TODO cross compiling? only works on aarch64 so far

# .config
# select none in arm cpu
# select kvm for platform
# enable exactly one tty

# To run the unikernel
qemu-system-aarch64 -kernel build/ssl_uk_qemu-arm64 -machine virt -cpu max -m 64M -nographic

# Debugging 
qemu-system-aarch64 -s -S -cpu max -machine virt -m 128M -nodefaults -no-acpi -display none -serial stdio -kernel build/ssl_uk_qemu-arm64 -append verbose

gdb --eval-command="target remote :1234" build/ssl_uk_qemu-arm64.dbg