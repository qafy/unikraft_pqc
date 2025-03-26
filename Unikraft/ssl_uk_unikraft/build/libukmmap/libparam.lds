SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libukmmap : {
  PROVIDE(uk_libparam_params_libukmmap_start = .);
  KEEP(*(.uk_libparam_params_libukmmap))
  KEEP(*(.uk_libparam_params_libukmmap.*))
  PROVIDE(uk_libparam_params_libukmmap_end = .);
 }
}
INSERT AFTER .rodata
