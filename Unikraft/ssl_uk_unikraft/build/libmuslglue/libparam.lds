SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libmuslglue : {
  PROVIDE(uk_libparam_params_libmuslglue_start = .);
  KEEP(*(.uk_libparam_params_libmuslglue))
  KEEP(*(.uk_libparam_params_libmuslglue.*))
  PROVIDE(uk_libparam_params_libmuslglue_end = .);
 }
}
INSERT AFTER .rodata
