SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libukboot : {
  PROVIDE(uk_libparam_params_libukboot_start = .);
  KEEP(*(.uk_libparam_params_libukboot))
  KEEP(*(.uk_libparam_params_libukboot.*))
  PROVIDE(uk_libparam_params_libukboot_end = .);
 }
}
INSERT AFTER .rodata
