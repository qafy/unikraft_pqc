SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libdevfs : {
  PROVIDE(uk_libparam_params_libdevfs_start = .);
  KEEP(*(.uk_libparam_params_libdevfs))
  KEEP(*(.uk_libparam_params_libdevfs.*))
  PROVIDE(uk_libparam_params_libdevfs_end = .);
 }
}
INSERT AFTER .rodata
