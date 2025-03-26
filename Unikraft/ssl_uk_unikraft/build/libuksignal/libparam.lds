SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libuksignal : {
  PROVIDE(uk_libparam_params_libuksignal_start = .);
  KEEP(*(.uk_libparam_params_libuksignal))
  KEEP(*(.uk_libparam_params_libuksignal.*))
  PROVIDE(uk_libparam_params_libuksignal_end = .);
 }
}
INSERT AFTER .rodata
