SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libsyscall_shim : {
  PROVIDE(uk_libparam_params_libsyscall_shim_start = .);
  KEEP(*(.uk_libparam_params_libsyscall_shim))
  KEEP(*(.uk_libparam_params_libsyscall_shim.*))
  PROVIDE(uk_libparam_params_libsyscall_shim_end = .);
 }
}
INSERT AFTER .rodata
