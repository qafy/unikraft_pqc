SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libukstreambuf : {
  PROVIDE(uk_libparam_params_libukstreambuf_start = .);
  KEEP(*(.uk_libparam_params_libukstreambuf))
  KEEP(*(.uk_libparam_params_libukstreambuf.*))
  PROVIDE(uk_libparam_params_libukstreambuf_end = .);
 }
}
INSERT AFTER .rodata
