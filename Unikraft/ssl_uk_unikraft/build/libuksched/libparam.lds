SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libuksched : {
  PROVIDE(uk_libparam_params_libuksched_start = .);
  KEEP(*(.uk_libparam_params_libuksched))
  KEEP(*(.uk_libparam_params_libuksched.*))
  PROVIDE(uk_libparam_params_libuksched_end = .);
 }
}
INSERT AFTER .rodata
