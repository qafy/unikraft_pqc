SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libukbus_platform : {
  PROVIDE(uk_libparam_params_libukbus_platform_start = .);
  KEEP(*(.uk_libparam_params_libukbus_platform))
  KEEP(*(.uk_libparam_params_libukbus_platform.*))
  PROVIDE(uk_libparam_params_libukbus_platform_end = .);
 }
}
INSERT AFTER .rodata
