SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libukschedcoop : {
  PROVIDE(uk_libparam_params_libukschedcoop_start = .);
  KEEP(*(.uk_libparam_params_libukschedcoop))
  KEEP(*(.uk_libparam_params_libukschedcoop.*))
  PROVIDE(uk_libparam_params_libukschedcoop_end = .);
 }
}
INSERT AFTER .rodata
