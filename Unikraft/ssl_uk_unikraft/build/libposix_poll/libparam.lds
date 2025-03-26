SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libposix_poll : {
  PROVIDE(uk_libparam_params_libposix_poll_start = .);
  KEEP(*(.uk_libparam_params_libposix_poll))
  KEEP(*(.uk_libparam_params_libposix_poll.*))
  PROVIDE(uk_libparam_params_libposix_poll_end = .);
 }
}
INSERT AFTER .rodata
