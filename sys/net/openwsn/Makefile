MODULE:=$(shell basename $(CURDIR))
INCLUDES += -I$(RIOTBASE) -I$(RIOTBASE)/sys/include -I$(RIOTBASE)/core/include -I$(RIOTBASE)/drivers/include -I$(RIOTBASE)/drivers/cc110x_ng/include -I$(RIOTBASE)/cpu/arm_common/include -I$(RIOTBASE)/sys/net/include/

DIRS += cross-layers
DIRS += 02a-MAClow
DIRS += 02b-MAChigh
DIRS += 03a-IPHC
DIRS += 03b-IPv6
DIRS += 04-TRAN
DIRS += 07-App

all:
	@for i in $(DIRS) ; do "$(MAKE)" -C $$i ; done ;

include $(RIOTBASE)/Makefile.base

# remove compilation products
clean::
	@for i in $(DIRS) ; do "$(MAKE)" -C $$i clean ; done ;
