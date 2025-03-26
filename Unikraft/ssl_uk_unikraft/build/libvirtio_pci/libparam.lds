SECTIONS {
 . = ALIGN(8);
 .uk_libparam_params_libvirtio_pci : {
  PROVIDE(uk_libparam_params_libvirtio_pci_start = .);
  KEEP(*(.uk_libparam_params_libvirtio_pci))
  KEEP(*(.uk_libparam_params_libvirtio_pci.*))
  PROVIDE(uk_libparam_params_libvirtio_pci_end = .);
 }
}
INSERT AFTER .rodata
