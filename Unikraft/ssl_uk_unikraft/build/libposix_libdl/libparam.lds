SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libposix_libdl : {
  PROVIDE(uk_libparam_params_libposix_libdl_start = .);
  KEEP(*(.uk_libparam_params_libposix_libdl))
  KEEP(*(.uk_libparam_params_libposix_libdl.*))
  PROVIDE(uk_libparam_params_libposix_libdl_end = .);
 }
}
INSERT AFTER .rodata
