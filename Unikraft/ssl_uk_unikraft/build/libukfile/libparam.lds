SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libukfile : {
  PROVIDE(uk_libparam_params_libukfile_start = .);
  KEEP(*(.uk_libparam_params_libukfile))
  KEEP(*(.uk_libparam_params_libukfile.*))
  PROVIDE(uk_libparam_params_libukfile_end = .);
 }
}
INSERT AFTER .rodata
