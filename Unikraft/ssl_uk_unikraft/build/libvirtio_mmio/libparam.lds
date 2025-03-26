SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libvirtio_mmio : {
  PROVIDE(uk_libparam_params_libvirtio_mmio_start = .);
  KEEP(*(.uk_libparam_params_libvirtio_mmio))
  KEEP(*(.uk_libparam_params_libvirtio_mmio.*))
  PROVIDE(uk_libparam_params_libvirtio_mmio_end = .);
 }
}
INSERT AFTER .rodata
