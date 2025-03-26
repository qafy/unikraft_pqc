SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libukatomic : {
  PROVIDE(uk_libparam_params_libukatomic_start = .);
  KEEP(*(.uk_libparam_params_libukatomic))
  KEEP(*(.uk_libparam_params_libukatomic.*))
  PROVIDE(uk_libparam_params_libukatomic_end = .);
 }
}
INSERT AFTER .rodata
