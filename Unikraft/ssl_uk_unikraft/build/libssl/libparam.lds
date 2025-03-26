SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libssl : {
  PROVIDE(uk_libparam_params_libssl_start = .);
  KEEP(*(.uk_libparam_params_libssl))
  KEEP(*(.uk_libparam_params_libssl.*))
  PROVIDE(uk_libparam_params_libssl_end = .);
 }
}
INSERT AFTER .rodata
