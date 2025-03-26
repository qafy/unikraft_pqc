SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libuknetdev : {
  PROVIDE(uk_libparam_params_libuknetdev_start = .);
  KEEP(*(.uk_libparam_params_libuknetdev))
  KEEP(*(.uk_libparam_params_libuknetdev.*))
  PROVIDE(uk_libparam_params_libuknetdev_end = .);
 }
}
INSERT AFTER .rodata
