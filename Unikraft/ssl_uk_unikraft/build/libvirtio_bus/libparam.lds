SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libvirtio_bus : {
  PROVIDE(uk_libparam_params_libvirtio_bus_start = .);
  KEEP(*(.uk_libparam_params_libvirtio_bus))
  KEEP(*(.uk_libparam_params_libvirtio_bus.*))
  PROVIDE(uk_libparam_params_libvirtio_bus_end = .);
 }
}
INSERT AFTER .rodata
