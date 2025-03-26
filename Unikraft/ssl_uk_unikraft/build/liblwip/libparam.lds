SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_liblwip : {
  PROVIDE(uk_libparam_params_liblwip_start = .);
  KEEP(*(.uk_libparam_params_liblwip))
  KEEP(*(.uk_libparam_params_liblwip.*))
  PROVIDE(uk_libparam_params_liblwip_end = .);
 }
}
INSERT AFTER .rodata
