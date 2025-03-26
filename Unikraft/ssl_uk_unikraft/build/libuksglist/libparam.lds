SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libuksglist : {
  PROVIDE(uk_libparam_params_libuksglist_start = .);
  KEEP(*(.uk_libparam_params_libuksglist))
  KEEP(*(.uk_libparam_params_libuksglist.*))
  PROVIDE(uk_libparam_params_libuksglist_end = .);
 }
}
INSERT AFTER .rodata
