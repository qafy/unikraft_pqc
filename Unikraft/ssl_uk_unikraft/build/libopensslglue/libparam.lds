SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libopensslglue : {
  PROVIDE(uk_libparam_params_libopensslglue_start = .);
  KEEP(*(.uk_libparam_params_libopensslglue))
  KEEP(*(.uk_libparam_params_libopensslglue.*))
  PROVIDE(uk_libparam_params_libopensslglue_end = .);
 }
}
INSERT AFTER .rodata
