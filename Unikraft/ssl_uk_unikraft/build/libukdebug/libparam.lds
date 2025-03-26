SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libukdebug : {
  PROVIDE(uk_libparam_params_libukdebug_start = .);
  KEEP(*(.uk_libparam_params_libukdebug))
  KEEP(*(.uk_libparam_params_libukdebug.*))
  PROVIDE(uk_libparam_params_libukdebug_end = .);
 }
}
INSERT AFTER .rodata
