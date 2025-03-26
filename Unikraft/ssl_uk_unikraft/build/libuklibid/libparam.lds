SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libuklibid : {
  PROVIDE(uk_libparam_params_libuklibid_start = .);
  KEEP(*(.uk_libparam_params_libuklibid))
  KEEP(*(.uk_libparam_params_libuklibid.*))
  PROVIDE(uk_libparam_params_libuklibid_end = .);
 }
}
INSERT AFTER .rodata
