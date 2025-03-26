SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libposix_pipe : {
  PROVIDE(uk_libparam_params_libposix_pipe_start = .);
  KEEP(*(.uk_libparam_params_libposix_pipe))
  KEEP(*(.uk_libparam_params_libposix_pipe.*))
  PROVIDE(uk_libparam_params_libposix_pipe_end = .);
 }
}
INSERT AFTER .rodata
