SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libuklock : {
  PROVIDE(uk_libparam_params_libuklock_start = .);
  KEEP(*(.uk_libparam_params_libuklock))
  KEEP(*(.uk_libparam_params_libuklock.*))
  PROVIDE(uk_libparam_params_libuklock_end = .);
 }
}
INSERT AFTER .rodata
