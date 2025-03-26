SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libukalloc : {
  PROVIDE(uk_libparam_params_libukalloc_start = .);
  KEEP(*(.uk_libparam_params_libukalloc))
  KEEP(*(.uk_libparam_params_libukalloc.*))
  PROVIDE(uk_libparam_params_libukalloc_end = .);
 }
}
INSERT AFTER .rodata
