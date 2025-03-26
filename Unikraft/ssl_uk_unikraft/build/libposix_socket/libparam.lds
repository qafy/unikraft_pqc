SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libposix_socket : {
  PROVIDE(uk_libparam_params_libposix_socket_start = .);
  KEEP(*(.uk_libparam_params_libposix_socket))
  KEEP(*(.uk_libparam_params_libposix_socket.*))
  PROVIDE(uk_libparam_params_libposix_socket_end = .);
 }
}
INSERT AFTER .rodata
