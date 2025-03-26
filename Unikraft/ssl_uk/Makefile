WITH_OPENSSL    ?= y
WITH_LWIP		?= y
WITH_MUSL		?= y
WITH_UKRANDOM	?= n

UK_ROOT  ?= $(PWD)/unikraft-0.17.0
UK_LIBS  ?= $(PWD)/libs
UK_BUILD ?= $(PWD)/build
UK_PLATS ?= $(PWD)/plats

LIBS-y                  := 
LIBS-$(WITH_OPENSSL)    := $(LIBS-y):$(UK_LIBS)/lib-openssl
LIBS-$(WITH_MUSL)		:= $(LIBS-y):$(UK_LIBS)/lib-musl
LIBS-$(WITH_LWIP)		:= $(LIBS-y):$(UK_LIBS)/lib-lwip
LIBS-$(WITH_UKRANDOM)	:= $(LIBS-y):$(UK_LIBS)/lib-ukrandom

PLATS-y                 :=

all:
	echo $(PWD)
	@$(MAKE) -C $(UK_ROOT) A=$(PWD) L=$(LIBS-y) O=$(UK_BUILD) P=$(PLATS-y)

$(MAKECMDGOALS):
	@$(MAKE) -C $(UK_ROOT) A=$(PWD) L=$(LIBS-y) O=$(UK_BUILD) P=$(PLATS-y) $(MAKECMDGOALS)
