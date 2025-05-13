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

sudo ip link add dev virbr0 type bridge
sudo ip address add 172.44.0.1/24 dev virbr0
sudo ip link set dev virbr0 up

sudo mkdir /etc/qemu
sudo echo "allow virbr0" > /etc/qemu/bridge.conf

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

Native/openssl req -x509 -new \
			-newkey dilithium3 \
			-keyout pki/CA_dil.key -out pki/CA_dil.crt \
			-nodes -subj "/CN=Test CA" -days 365

Native/openssl req -new \
			-newkey dilithium3 \
			-keyout pki/server_dil.key -out pki/server_dil.csr \
			-nodes -subj "/CN=testserver"

Native/openssl x509 -req \
			 -in pki/server_dil.csr -out pki/server_dil.crt \
			 -CA pki/CA_dil.crt -CAkey pki/CA_dil.key -CAcreateserial -days 365


Native/openssl s_server -key pki/server_dil.key -cert pki/server_dil.crt -accept 443 -www
Native/openssl s_client -connect localhost:443 -verifyCAfile pki/CA_dil.crt -ign_eof -nocommands

Unikraft/openssl s_server -key pki/server_dil.key -cert pki/server_dil.crt -accept 443 -www
Native/openssl s_client -connect 172.44.0.2:443 -verifyCAfile pki/CA_dil.crt -ign_eof -nocommands

Native/openssl s_server -key pki/server_dil.key -cert pki/server_dil.crt -accept 443 -www
Unikraft/openssl s_client -connect 172.44.0.1:443 -verifyCAfile pki/CA_dil.crt -ign_eof -nocommands

Native/openssl s_server -key pki/server_dil.key -cert pki/server_dil.crt -accept 443 -www
Native/openssl s_time -connect localhost:443 -www / -CAfile pki/CA_dil.crt

Unikraft/openssl s_time -connect 172.44.0.1:443 -www / -CAfile pki/CA_dil.crt

Container/openssl s_client -connect 10.1.1.155:443 
does not work yet
// -verifyCAfile pki/CA_dil.crt -ign_eof -nocommands

- tls connection is possible, however there is no certificate checking yet
- kem is possible and is used to set a custom kem function
- problem: how to test if kem is working?
- signature and kem algorithms are displayed on startup
- do not use file system for test application because reconfiguration and unikernel is supposed to be minimal

- TODO use builtin libssl functions to load certificate
- TODO adjust container to be able to use liboqs with oqsprovider and s_server
- Optional port apps s_server and s_speed to unikraft and use them for benchmarking purposes, 
pobably have to turn on filesystem and virtual memory for this

- TODO '-Wl,-rpath,$(LIBRPATH)' is not configured for the docker file, is not needed since we do not use the openssl bin, but if we want to we need to adjust this

# kvm on pi

- first getrandom was not implemented, patch proposed on discord, did not work bc depends on lots of other patches
- upgraded to latest version 18 of unikraft
- still throws cpu exception
- crashes in tcpip_init in the lwip network stack
- seems to come from a either semaphore down or wzr register
- was not the wzr register
- there were also dependency issues in the uk config
- building on the pi did not make a difference, same error occurs
- updating to the most recent commit of unikraft helped, commit Tue Mar 18 5050e9f11e57a17bd18d4f1a3478010b329c6855
- unikraft needs patch in poll -> poll_select

# To run the unikernel
qemu-system-aarch64 -kernel build/ssl_uk_qemu-arm64 -machine virt -cpu max -m 64M -nographic

# Debugging 
qemu-system-aarch64 -s -S -cpu max -machine virt -m 128M -nodefaults -no-acpi -display none -serial stdio -kernel build/ssl_uk_qemu-arm64 -append verbose

gdb --eval-command="target remote :1234" build/ssl_uk_qemu-arm64.dbg

# reproducing the libraries

libraries so far are used in the static library form .a and built manually
create repoducible way to build libraries inside the uk_build_aarch64 docker file
patched musl version is setup to compile the libraries
libraries are compiled inside the docker container 
everything is installed in the folder /opt/oqssa

# unified setup

call ./setup.sh in the folders Container/Native
will generate openssl link that starts openssl binary in container

# tests

use liboqs tests and oqsprovider tests

never finishes in a loop
gdb still steps through
stdout is not working anymore
on next print call everything gets stuck

Single stepping until exit from function OQS_KEM_bike_l1_decode,
which has no line number information.
memcpy (dest=0x403ab840, src=0x403aa600, n=1541) at /workspace/Unikraft/ssl_uk/build/libmusl/origin/musl-1.2.3//src/string/memcpy.c:23
23              for (; (uintptr_t)s % 4 && n; n--) *d++ = *s++;
(gdb) finish
Run till exit from #0  memcpy (dest=0x403ab840, src=0x403aa600, n=1541)
    at /workspace/Unikraft/ssl_uk/build/libmusl/origin/musl-1.2.3//src/string/memcpy.c:23
0x0000000040224764 in OQS_KEM_bike_l1_decode ()
Value returned is $22 = (void *) 0x403ab840
(gdb) call printf("Hi\n")

320 440 
br OQS_KEM_bike_l1_decode
br OQS_KEM_bike_l1_gf2x_mod_mul
br OQS_KEM_bike_l1_gf2x_mod_mul_with_ctx

gf2x_mod_mul_with_ctx
between 1000 1500#

uses karatsuba algorithms with recursion
solution increase stack size to make it run (8 Pages so far)

not all tests pass bc not all algorithms are enabled
TODO do we need to support all of them?

done in ssl_uk_test also prints the version available ciphers and
TODO does a self connection to check if everything works


# benchmarks

internal benchmarks done in oqs_uk_speed also taken from liboqs, test the speed of KEM and Signature algorithms

TODO match the configs of openssl + liboqs from container, native, Unikernel

# openssl binary

enabled 9pfs to access config
statically add oqsprovider
added s_server, s_client, s_time parts of openssl
64M is not enough memory, increased to 128M

Certificate verification shows that certificate is only valid later
system time wrong? 

TODO container does not load oqsprovider as additional provider, otherwise config file has to be specified for each cmd manually

# benchmarks

TODO find a way to get the ip address from the dock

TODO for power measurement, draw a diagram of the connections (resistor etc)

TODO inform about basics electrical engineering, voltage splitter

TODO also check memory consumption, look for good profiler for this


most important kyber, falcon, dilithium, sphincs
interesting lms xms
less interesting frodokem, bike


TODO find a way to reliably kill the openssl processes, with s_client you have to use Q in stdin to terminate it, Unikraft does not have stdin, find a way to terminate this as well, s_server does neet ctrl-c, the binaries we provide (Unikraft/openssl) are scripts that then execute the right configuration with e.g. qemu, if we cancel this script maybe qemu is not termianted as well

# on pi 

CMake Error at CMakeLists.txt:64 (find_package):
  By not providing "Findliboqs.cmake" in CMAKE_MODULE_PATH this project has
  asked CMake to find a package configuration file provided by "liboqs", but
  CMake did not find one.

  Could not find a package configuration file provided by "liboqs" with any
  of the following names:

    liboqsConfig.cmake
    liboqs-config.cmake

  Add the installation prefix of "liboqs" to CMAKE_PREFIX_PATH or set
  "liboqs_DIR" to a directory containing one of the above files.  If "liboqs"
  provides a separate development package or SDK, be sure it has been
  installed.

TODO setup script did not work, few changes are made on the pi cant push move manually