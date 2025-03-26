SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libposix_futex : {
  PROVIDE(uk_libparam_params_libposix_futex_start = .);
  KEEP(*(.uk_libparam_params_libposix_futex))
  KEEP(*(.uk_libparam_params_libposix_futex.*))
  PROVIDE(uk_libparam_params_libposix_futex_end = .);
 }
}
INSERT AFTER .rodata
