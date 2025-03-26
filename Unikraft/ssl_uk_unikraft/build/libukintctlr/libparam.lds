SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libukintctlr : {
  PROVIDE(uk_libparam_params_libukintctlr_start = .);
  KEEP(*(.uk_libparam_params_libukintctlr))
  KEEP(*(.uk_libparam_params_libukintctlr.*))
  PROVIDE(uk_libparam_params_libukintctlr_end = .);
 }
}
INSERT AFTER .rodata
