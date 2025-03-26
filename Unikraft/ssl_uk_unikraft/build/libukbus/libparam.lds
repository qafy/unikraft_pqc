SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libukbus : {
  PROVIDE(uk_libparam_params_libukbus_start = .);
  KEEP(*(.uk_libparam_params_libukbus))
  KEEP(*(.uk_libparam_params_libukbus.*))
  PROVIDE(uk_libparam_params_libukbus_end = .);
 }
}
INSERT AFTER .rodata
