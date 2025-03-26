SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libposix_fdio : {
  PROVIDE(uk_libparam_params_libposix_fdio_start = .);
  KEEP(*(.uk_libparam_params_libposix_fdio))
  KEEP(*(.uk_libparam_params_libposix_fdio.*))
  PROVIDE(uk_libparam_params_libposix_fdio_end = .);
 }
}
INSERT AFTER .rodata
