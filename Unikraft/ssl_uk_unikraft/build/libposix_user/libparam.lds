SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libposix_user : {
  PROVIDE(uk_libparam_params_libposix_user_start = .);
  KEEP(*(.uk_libparam_params_libposix_user))
  KEEP(*(.uk_libparam_params_libposix_user.*))
  PROVIDE(uk_libparam_params_libposix_user_end = .);
 }
}
INSERT AFTER .rodata
