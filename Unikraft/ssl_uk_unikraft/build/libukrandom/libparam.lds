SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libukrandom : {
  PROVIDE(uk_libparam_params_libukrandom_start = .);
  KEEP(*(.uk_libparam_params_libukrandom))
  KEEP(*(.uk_libparam_params_libukrandom.*))
  PROVIDE(uk_libparam_params_libukrandom_end = .);
 }
}
INSERT AFTER .rodata
