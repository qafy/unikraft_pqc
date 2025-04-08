#!/usr/bin/env sh

if [ "$1" = "native" ]; then

# native elf-loader with initrd and bridge networking
./qemu/build/qemu-system-x86_64 \
	-cdrom kernel.iso -boot d\
	-drive if=pflash,format=raw,readonly=on,file=OVMF/OVMF_CODE.fd \
	-nographic \
	-m 1G \
	-enable-kvm \
	-cpu host -smp 4 \
	-monitor pty \
    -nographic \
    -netdev bridge,id=en0,br=virbr0,helper=bin/qemu-bridge-helper \
    -device virtio-net-pci,netdev=en0 \
    | tee -a logs/elf.log

else

./qemu/build/qemu-system-x86_64 \
    -enable-kvm \
    -cpu EPYC-v4 \
    -machine q35  \
    -smp 1 \
    -m 2048M,slots=5,maxmem=10240M \
    -no-reboot \
    -drive if=pflash,format=raw,unit=0,file=OVMF/OVMF_CODE.fd,readonly \
    -drive file=kernel.iso,media=cdrom \
    -boot d \
    -netdev bridge,id=en0,br=virbr0,helper=bin/qemu-bridge-helper \
    -device virtio-net-pci,netdev=en0,disable-legacy=on,iommu_platform=false \
    -machine memory-encryption=sev0,vmport=off \
    -object memory-backend-memfd-private,id=ram1,size=2048M,share=true \
    -object sev-snp-guest,id=sev0,cbitpos=51,reduced-phys-bits=1,discard=none \
    -machine memory-backend=ram1,kvm-type=protected \
    -monitor telnet:127.0.0.1:1234,server,nowait \
    -nographic \
    | tee -a logs/elf.log

fi


# kraft generates parameters similar to this
# qemu-system-x86_64 \
#     -enable-kvm \
#     -cpu EPYC-v4 -machine q35 \
#     -smp 4,maxcpus=255 \
#     -m 4G,slots=5,maxmem=20G \
#     -no-reboot \
#     -monitor pty \
#     -serial mon:stdio \
#     -nographic \
#     -netdev user,id=vmnic,hostfwd=tcp::8080-:8080 \
#     -device virtio-net-pci,netdev=vmnic,romfile= \
#     -kernel /workspace/app-httpreply/workdir/build/app-httpreply_qemu-x86_64 


# native EFI Stub boot
# ./qemu/build/qemu-system-x86_64 \
# 	-cdrom kernel.iso -boot d\
# 	-drive if=pflash,format=raw,readonly=on,file=OVMF/OVMF_CODE.fd \
# 	-nographic \
# 	-m 1G \
# 	-enable-kvm \
# 	-cpu host -smp 4 \
# 	-monitor pty


# AMD SEV-SNP boot without any interfaces
# ./qemu/build/qemu-system-x86_64 \
#     -enable-kvm \
#     -cpu EPYC-v4 -machine q35 \
#     -smp 4,maxcpus=255 \
#     -m 4G,slots=5,maxmem=20G \
#     -no-reboot \
#     -drive if=pflash,format=raw,unit=0,file=OVMF/OVMF_CODE.fd,readonly=on \
#     -drive file=kernel.iso,media=cdrom \
#     -boot d \
#     -machine memory-encryption=sev0,vmport=off \
#     -object memory-backend-memfd-private,id=ram1,size=2048M,share=true \
#     -object sev-snp-guest,id=sev0,cbitpos=51,reduced-phys-bits=1,discard=none \
#     -machine memory-backend=ram1,kvm-type=protected \
#     -nographic -monitor pty -monitor unix:monitor,server,nowait \
#     -serial mon:stdio \
#     -nodefaults


# AMD SEV-SNP boot with user network interface
# ./qemu/build/qemu-system-x86_64 \
#     -enable-kvm \
#     -cpu EPYC-v4 -machine q35 \
#     -smp 4,maxcpus=255 \
#     -m 4G,slots=5,maxmem=20G \
#     -no-reboot \
#     -drive if=pflash,format=raw,unit=0,file=OVMF/OVMF_CODE.fd,readonly=on \
#     -drive file=kernel.iso,media=cdrom \
#     -boot d \
#     -monitor pty -monitor unix:monitor,server,nowait \
#     -serial mon:stdio \
#     -nographic \
#     -netdev user,id=vmnic,hostfwd=tcp::8080-:8080 \
#     -device virtio-net-pci,netdev=vmnic,romfile= \
#     -machine memory-encryption=sev0,vmport=off \
#     -object memory-backend-memfd-private,id=ram1,size=2048M,share=true \
#     -object sev-snp-guest,id=sev0,cbitpos=51,reduced-phys-bits=1,discard=none \
#     -machine memory-backend=ram1,kvm-type=protected \
#     | tee -a logs/http.log


# AMD SEV-SNP boot with bridge network interface
# ./qemu/build/qemu-system-x86_64 \
#     -enable-kvm \
#     -cpu EPYC-v4 \
#     -machine q35  \
#     -smp 4,maxcpus=255 \
#     -m 2048M,slots=5,maxmem=10240M \
#     -no-reboot \
#     -drive if=pflash,format=raw,unit=0,file=OVMF/OVMF_CODE.fd,readonly \
#     -drive file=kernel.iso,media=cdrom \
#     -boot d \
#     -netdev bridge,id=en0,br=virbr0,helper=bin/qemu-bridge-helper \
#     -device virtio-net-pci,netdev=en0,disable-legacy=on,iommu_platform=false \
#     -machine memory-encryption=sev0,vmport=off \
#     -object memory-backend-memfd-private,id=ram1,size=2048M,share=true \
#     -object sev-snp-guest,id=sev0,cbitpos=51,reduced-phys-bits=1,discard=none \
#     -machine memory-backend=ram1,kvm-type=protected \
#     -monitor telnet:127.0.0.1:1234,server,nowait \
#     -nographic \
#     | tee -a logs/output_plain.log


# native elf-loader with fsdev
# rootfs="../dynamic-apps/lang/c/helloworld"
# qemu-system-x86_64 \
#     -kernel "$kernel" \
#     -nographic \
#     -m 64M \
#     -append "/helloworld" \
#     -fsdev local,id=myid,path="$rootfs",security_model=none \
#     -device virtio-9p-pci,fsdev=myid,mount_tag=fs1,disable-modern=on,disable-legacy=off \
#     -cpu max


# AMD SEV-SNP boot with network interface and rootfs
# ./qemu/build/qemu-system-x86_64 \
#     -enable-kvm \
#     -cpu EPYC-v4 -machine q35 \
#     -smp 4,maxcpus=255 \
#     -m 4G,slots=5,maxmem=20G \
#     -no-reboot \
#     -drive if=pflash,format=raw,unit=0,file=OVMF/OVMF_CODE.fd,readonly=on \
#     -drive file=kernel.iso,media=cdrom \
#     -boot d \
#     -machine memory-encryption=sev0,vmport=off \
#     -object memory-backend-memfd-private,id=ram1,size=2048M,share=true \
#     -object sev-snp-guest,id=sev0,cbitpos=51,reduced-phys-bits=1,discard=none \
#     -machine memory-backend=ram1,kvm-type=protected \
#     -nographic -monitor pty -monitor unix:monitor,server,nowait \
#     -serial mon:stdio \
#     -nodefaults \
#     -netdev user,id=vmnic,hostfwd=tcp::5555-:8123 \
#     -device virtio-net-pci,disable-legacy=on,iommu_platform=true,netdev=vmnic,romfile= \
#     -fsdev local,id=myid,path="$(pwd)/app-python/rootfs",security_model=none \
#     -device virtio-9p-pci,fsdev=myid,mount_tag=fs1,disable-modern=on,disable-legacy=off \
#     | tee -a logs/http.log

# IMPORTANT, Unikraft devs never use -nodefaults, always use just -nographics


