# Dependencies
- openssl-3.4.1
- liboqs-0.12.0
- oqs-provider-0.8.0

## Configuration for openssl
./Configure \
		CC=/workspace/Native/musl-install/bin/musl-gcc \
		--prefix=/workspace/Native/opt \
		--openssldir=/workspace/Native/usr/local \
		--with-rand-seed=getrandom \
		no-async \
		no-docs \
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



make
make install


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
- check for __attribute__((constructor)) to see library intizializes something and causes the crash
- check for sigsetjmp that this may cause the crash
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

## Musl setup + linux-headers
./configure --prefix=/workspace/Native/musl-install/ --syslibdir=/workspace/Native/musl-install/syslibdir/ 
make install

https://mirrors.edge.kernel.org/pub/linux/kernel/v6.x/linux-6.12.6.tar.xz
make headers ARCH="arm64"
- copy usr/include into musl-insall/include

- Configure musl-gcc path with CC= in openssl configuration script

- Compilation will fail but the libcrypto is produced still have to look at a fix for this
- possible fix https://www.openwall.com/lists/musl/2023/10/12/3

- TODO cross compiling? only tested on aarch64 so far
- TODO write patch for musl aligned_alloc

# .config
- select none in arm cpu
- select kvm for platform
- enable exactly one tty

## Configuration for liboqs
mkdir build && cd build
cmake .. -DOQS_USE_OPENSSL=OFF -DCMAKE_INSTALL_PREFIX=/workspace/Native/opt -DCMAKE_C_COMPILER=/workspace/Native/musl-install/bin/musl-gcc
cmake --build .
cmake --install .
- TODO OQS_USE_OPENSSL depends on openssl and will look for openssl during compilation, but gives better performance include this

## Configuration for oqs-provider
export liboqs_DIR="/workspace/Native/opt"
export OPENSSL_INSTALL="/workspace/Native/opt"
export CMAKE_PARAMS="-DCMAKE_C_COMPILER=/workspace/Native/musl-install/bin/musl-gcc -DOQS_PROVIDER_BUILD_STATIC=ON -DCMAKE_INSTALL_PREFIX=/workspace/Native/opt"
./scripts/fullbuild.sh
cmake --install _build

# Networking 


ip link add dev virbr0 type bridge
ip address add 172.44.0.1/24 dev virbr0
ip link set dev virbr0 up

qemu-system-aarch64 \
	-kernel build/ssl_uk_qemu-arm64 \
	-machine virt -cpu max -m 64M \
	-nographic \
	-netdev bridge,id=en0,br=virbr0 \
    -device virtio-net-pci,netdev=en0 \
	-append "ssl_uk netdev.ip=172.44.0.2/24:172.44.0.1::: -- "


- Networking fails need:
- lwip
- uknetdev
- param LIBUKNETDEV_EINFO_LIBPARAM
- bridge see above

- Printf fails need: 
drivers->console->pl011 and enable early console. For qemu-system-aarch64/virt the pl011 is at 0x09000000

# TLS networking

openssl req -x509 -new \
			-newkey dilithium3 \
			-keyout CA.key -out pki/CA.crt \
			-nodes -subj "/CN=Test CA" -days 365 \
			-config /workspace/container-files/openssl.cnf

openssl req -new \
			-newkey dilithium3 \
			-keyout pki/server.key -out pki/server.csr \
			-nodes -subj "/CN=testserver" \
			-config /workspace/container-files/openssl.cnf

openssl x509 -req \
			 -in pki/server.csr -out pki/server.crt \
			 -CA pki/CA.crt -CAkey CA.key -CAcreateserial -days 365

for quick test use this:
openssl s_server -key pki/server.key -cert pki/server.crt -accept 443 -www

# To run the unikernel
qemu-system-aarch64 -kernel build/ssl_uk_qemu-arm64 -machine virt -cpu max -m 64M -nographic

# Debugging 
qemu-system-aarch64 -s -S -cpu max -machine virt -m 128M -nodefaults -no-acpi -display none -serial stdio -kernel build/ssl_uk_qemu-arm64 -append verbose

gdb --eval-command="target remote :1234" build/ssl_uk_qemu-arm64.dbg