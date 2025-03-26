SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libukbitops : {
  PROVIDE(uk_libparam_params_libukbitops_start = .);
  KEEP(*(.uk_libparam_params_libukbitops))
  KEEP(*(.uk_libparam_params_libukbitops.*))
  PROVIDE(uk_libparam_params_libukbitops_end = .);
 }
}
INSERT AFTER .rodata
