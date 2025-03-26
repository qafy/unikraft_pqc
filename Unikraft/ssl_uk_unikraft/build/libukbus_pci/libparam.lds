SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libukbus_pci : {
  PROVIDE(uk_libparam_params_libukbus_pci_start = .);
  KEEP(*(.uk_libparam_params_libukbus_pci))
  KEEP(*(.uk_libparam_params_libukbus_pci.*))
  PROVIDE(uk_libparam_params_libukbus_pci_end = .);
 }
}
INSERT AFTER .rodata
