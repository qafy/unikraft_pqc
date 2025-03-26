SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libukintctlr_xpic : {
  PROVIDE(uk_libparam_params_libukintctlr_xpic_start = .);
  KEEP(*(.uk_libparam_params_libukintctlr_xpic))
  KEEP(*(.uk_libparam_params_libukintctlr_xpic.*))
  PROVIDE(uk_libparam_params_libukintctlr_xpic_end = .);
 }
}
INSERT AFTER .rodata
