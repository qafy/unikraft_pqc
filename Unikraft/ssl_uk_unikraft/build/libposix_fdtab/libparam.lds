SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libposix_fdtab : {
  PROVIDE(uk_libparam_params_libposix_fdtab_start = .);
  KEEP(*(.uk_libparam_params_libposix_fdtab))
  KEEP(*(.uk_libparam_params_libposix_fdtab.*))
  PROVIDE(uk_libparam_params_libposix_fdtab_end = .);
 }
}
INSERT AFTER .rodata
