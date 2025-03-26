deps_config := \
	/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft/build/kconfig/app.uk \
	/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_native/.unikraft/unikraft/lib/ukrandom/Config.uk \
	/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft/libs/lib-lwip/Config.uk \
	/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft/libs/lib-musl/Config.uk \
	/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft/libs/lib-openssl/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/vfscore/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/ukvmem/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/uktimeconv/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/uktest/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/ukswrand/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/ukstreambuf/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/ukstore/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/uksp/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/uksignal/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/uksglist/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/ukschedcoop/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/uksched/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/ukrust/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/ukring/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/ukreloc/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/ukofw/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/uknofault/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/uknetdev/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/ukmpi/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/ukmmap/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/uklock/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/uklibparam/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/uklibid/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/ukintctlr/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/ukgcov/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/ukfile/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/ukfallocbuddy/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/ukfalloc/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/ukdebug/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/ukcpio/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/ukbus/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/ukboot/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/ukblkdev/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/ukbitops/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/ukatomic/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/ukargparse/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/ukallocregion/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/ukallocpool/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/ukallocbbuddy/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/ukalloc/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/uk9p/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/ubsan/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/syscall_shim/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/ramfs/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/posix-user/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/posix-unixsocket/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/posix-timerfd/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/posix-time/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/posix-sysinfo/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/posix-socket/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/posix-process/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/posix-poll/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/posix-pipe/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/posix-mmap/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/posix-libdl/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/posix-futex/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/posix-fdtab/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/posix-fdio/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/posix-eventfd/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/posix-environ/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/nolibc/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/isrlib/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/fdt/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/devfs/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib/9pfs/Config.uk \
	/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft/build/kconfig/libs.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/drivers/xen/xenbus/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/drivers/xen/net/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/drivers/xen/blk/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/drivers/xen/9p/Config.uk \
	/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft/build/kconfig/drivers-xen.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/drivers/virtio/ring/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/drivers/virtio/pci/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/drivers/virtio/net/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/drivers/virtio/mmio/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/drivers/virtio/bus/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/drivers/virtio/blk/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/drivers/virtio/9p/Config.uk \
	/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft/build/kconfig/drivers-virtio.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/drivers/ukintctlr/xpic/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/drivers/ukintctlr/gic/Config.uk \
	/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft/build/kconfig/drivers-intctlr.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/drivers/ukbus/platform/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/drivers/ukbus/pci/Config.uk \
	/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft/build/kconfig/drivers-bus.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/drivers/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/drivers/virtio/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/drivers/uktty/ns16550/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/drivers/uktty/pl011/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/drivers/uktty/Config.uk \
	/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft/build/kconfig/drivers.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/plat/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/plat/xen/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/plat/linuxu/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/plat/kvm/Config.uk \
	/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft/build/kconfig/plats.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/arch/arm/arm64/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/arch/arm/arm/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/arch/x86/x86_64/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/arch/Config.uk \
	/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/Config.uk

/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft/build/kconfig/auto.conf: \
	$(deps_config)

ifneq "$(UK_FULLVERSION)" "0.16.3~e79bb81"
/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft/build/kconfig/auto.conf: FORCE
endif
ifneq "$(UK_CODENAME)" "Telesto"
/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft/build/kconfig/auto.conf: FORCE
endif
ifneq "$(UK_ARCH)" "x86_64"
/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft/build/kconfig/auto.conf: FORCE
endif
ifneq "$(HOST_ARCH)" "x86_64"
/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft/build/kconfig/auto.conf: FORCE
endif
ifneq "$(UK_BASE)" "/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3"
/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft/build/kconfig/auto.conf: FORCE
endif
ifneq "$(UK_APP)" "/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft"
/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft/build/kconfig/auto.conf: FORCE
endif
ifneq "$(UK_NAME)" "ssl_uk_unikraft"
/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft/build/kconfig/auto.conf: FORCE
endif
ifneq "$(KCONFIG_DIR)" "/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft/build/kconfig"
/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft/build/kconfig/auto.conf: FORCE
endif
ifneq "$(KCONFIG_PLAT_BASE)" "/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/plat"
/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft/build/kconfig/auto.conf: FORCE
endif
ifneq "$(KCONFIG_EPLAT_DIRS)" ""
/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft/build/kconfig/auto.conf: FORCE
endif
ifneq "$(KCONFIG_EXCLUDEDIRS)" ""
/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft/build/kconfig/auto.conf: FORCE
endif
ifneq "$(KCONFIG_DRIV_BASE)" "/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/drivers"
/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft/build/kconfig/auto.conf: FORCE
endif
ifneq "$(KCONFIG_LIB_BASE)" "/home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/lib"
/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft/build/kconfig/auto.conf: FORCE
endif
ifneq "$(KCONFIG_ELIB_DIRS)" ":/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft/libs/lib-openssl:/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft/libs/lib-musl:/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft/libs/lib-lwip:/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft/libs/lib-ukrandom"
/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft/build/kconfig/auto.conf: FORCE
endif
ifneq "$(KCONFIG_EAPP_DIR)" "/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft"
/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft/build/kconfig/auto.conf: FORCE
endif

$(deps_config): ;
