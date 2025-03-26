SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libcrypto : {
  PROVIDE(uk_libparam_params_libcrypto_start = .);
  KEEP(*(.uk_libparam_params_libcrypto))
  KEEP(*(.uk_libparam_params_libcrypto.*))
  PROVIDE(uk_libparam_params_libcrypto_end = .);
 }
}
INSERT AFTER .rodata
