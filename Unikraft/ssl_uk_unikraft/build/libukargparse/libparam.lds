SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libukargparse : {
  PROVIDE(uk_libparam_params_libukargparse_start = .);
  KEEP(*(.uk_libparam_params_libukargparse))
  KEEP(*(.uk_libparam_params_libukargparse.*))
  PROVIDE(uk_libparam_params_libukargparse_end = .);
 }
}
INSERT AFTER .rodata
