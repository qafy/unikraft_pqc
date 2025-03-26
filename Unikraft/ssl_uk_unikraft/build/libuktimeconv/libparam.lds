SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libuktimeconv : {
  PROVIDE(uk_libparam_params_libuktimeconv_start = .);
  KEEP(*(.uk_libparam_params_libuktimeconv))
  KEEP(*(.uk_libparam_params_libuktimeconv.*))
  PROVIDE(uk_libparam_params_libuktimeconv_end = .);
 }
}
INSERT AFTER .rodata
