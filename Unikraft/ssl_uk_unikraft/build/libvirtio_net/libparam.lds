SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libvirtio_net : {
  PROVIDE(uk_libparam_params_libvirtio_net_start = .);
  KEEP(*(.uk_libparam_params_libvirtio_net))
  KEEP(*(.uk_libparam_params_libvirtio_net.*))
  PROVIDE(uk_libparam_params_libvirtio_net_end = .);
 }
}
INSERT AFTER .rodata
