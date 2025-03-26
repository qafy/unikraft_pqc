SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libukmpi : {
  PROVIDE(uk_libparam_params_libukmpi_start = .);
  KEEP(*(.uk_libparam_params_libukmpi))
  KEEP(*(.uk_libparam_params_libukmpi.*))
  PROVIDE(uk_libparam_params_libukmpi_end = .);
 }
}
INSERT AFTER .rodata
