SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libcontext : {
  PROVIDE(uk_libparam_params_libcontext_start = .);
  KEEP(*(.uk_libparam_params_libcontext))
  KEEP(*(.uk_libparam_params_libcontext.*))
  PROVIDE(uk_libparam_params_libcontext_end = .);
 }
}
INSERT AFTER .rodata
