SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libvfscore : {
  PROVIDE(uk_libparam_params_libvfscore_start = .);
  KEEP(*(.uk_libparam_params_libvfscore))
  KEEP(*(.uk_libparam_params_libvfscore.*))
  PROVIDE(uk_libparam_params_libvfscore_end = .);
 }
}
INSERT AFTER .rodata
