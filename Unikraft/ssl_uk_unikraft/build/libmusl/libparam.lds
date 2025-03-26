SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libmusl : {
  PROVIDE(uk_libparam_params_libmusl_start = .);
  KEEP(*(.uk_libparam_params_libmusl))
  KEEP(*(.uk_libparam_params_libmusl.*))
  PROVIDE(uk_libparam_params_libmusl_end = .);
 }
}
INSERT AFTER .rodata
