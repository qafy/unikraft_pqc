SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libkvmplat : {
  PROVIDE(uk_libparam_params_libkvmplat_start = .);
  KEEP(*(.uk_libparam_params_libkvmplat))
  KEEP(*(.uk_libparam_params_libkvmplat.*))
  PROVIDE(uk_libparam_params_libkvmplat_end = .);
 }
}
INSERT AFTER .rodata
