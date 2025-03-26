SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libukboot_main : {
  PROVIDE(uk_libparam_params_libukboot_main_start = .);
  KEEP(*(.uk_libparam_params_libukboot_main))
  KEEP(*(.uk_libparam_params_libukboot_main.*))
  PROVIDE(uk_libparam_params_libukboot_main_end = .);
 }
}
INSERT AFTER .rodata
