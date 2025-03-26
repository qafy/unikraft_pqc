cmd_/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft/build/libkvmplat/link64.lds := /bin/bash /home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft/build/libkvmplat/link64.lds.cmd

source_/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft/build/libkvmplat/link64.lds := /home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/plat/kvm/x86/link64.lds.S

deps_/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft/build/libkvmplat/link64.lds := \
  /home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/include/uk/arch/limits.h \
  /home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/include/uk/config.h \
  /home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/arch/x86/x86_64/include/uk/asm/limits.h \
    $(wildcard include/config/stack/size/page/order.h) \
    $(wildcard include/config/cpu/except/stack/size/page/order.h) \
  /home/chio/Documents/projects/Studenten/duiue/unikraft/unikraft-0.16.3/plat/common/include/uk/plat/common/common.lds.h \

/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft/build/libkvmplat/link64.lds: $(deps_/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft/build/libkvmplat/link64.lds)

$(deps_/home/chio/Documents/projects/pqc-vs-unikernel/02_unikernel/ssl_uk_unikraft/build/libkvmplat/link64.lds):
