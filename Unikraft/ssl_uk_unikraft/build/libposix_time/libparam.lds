SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libposix_time : {
  PROVIDE(uk_libparam_params_libposix_time_start = .);
  KEEP(*(.uk_libparam_params_libposix_time))
  KEEP(*(.uk_libparam_params_libposix_time.*))
  PROVIDE(uk_libparam_params_libposix_time_end = .);
 }
}
INSERT AFTER .rodata
