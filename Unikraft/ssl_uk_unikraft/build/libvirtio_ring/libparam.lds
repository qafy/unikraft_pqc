SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libvirtio_ring : {
  PROVIDE(uk_libparam_params_libvirtio_ring_start = .);
  KEEP(*(.uk_libparam_params_libvirtio_ring))
  KEEP(*(.uk_libparam_params_libvirtio_ring.*))
  PROVIDE(uk_libparam_params_libvirtio_ring_end = .);
 }
}
INSERT AFTER .rodata
