SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libukallocbbuddy : {
  PROVIDE(uk_libparam_params_libukallocbbuddy_start = .);
  KEEP(*(.uk_libparam_params_libukallocbbuddy))
  KEEP(*(.uk_libparam_params_libukallocbbuddy.*))
  PROVIDE(uk_libparam_params_libukallocbbuddy_end = .);
 }
}
INSERT AFTER .rodata
