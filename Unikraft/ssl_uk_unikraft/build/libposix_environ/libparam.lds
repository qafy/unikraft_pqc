SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libposix_environ : {
  PROVIDE(uk_libparam_params_libposix_environ_start = .);
  KEEP(*(.uk_libparam_params_libposix_environ))
  KEEP(*(.uk_libparam_params_libposix_environ.*))
  PROVIDE(uk_libparam_params_libposix_environ_end = .);
 }
}
INSERT AFTER .rodata
