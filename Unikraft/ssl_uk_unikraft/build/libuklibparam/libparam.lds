SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libuklibparam : {
  PROVIDE(uk_libparam_params_libuklibparam_start = .);
  KEEP(*(.uk_libparam_params_libuklibparam))
  KEEP(*(.uk_libparam_params_libuklibparam.*))
  PROVIDE(uk_libparam_params_libuklibparam_end = .);
 }
}
INSERT AFTER .rodata
