SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libposix_process : {
  PROVIDE(uk_libparam_params_libposix_process_start = .);
  KEEP(*(.uk_libparam_params_libposix_process))
  KEEP(*(.uk_libparam_params_libposix_process.*))
  PROVIDE(uk_libparam_params_libposix_process_end = .);
 }
}
INSERT AFTER .rodata
