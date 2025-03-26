SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_appopenssl : {
  PROVIDE(uk_libparam_params_appopenssl_start = .);
  KEEP(*(.uk_libparam_params_appopenssl))
  KEEP(*(.uk_libparam_params_appopenssl.*))
  PROVIDE(uk_libparam_params_appopenssl_end = .);
 }
}
INSERT AFTER .rodata
