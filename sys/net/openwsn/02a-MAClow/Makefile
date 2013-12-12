MODULE:=$(shell basename $(CURDIR))
INCLUDES += -I$(RIOTBASE) -I$(RIOTBASE)/sys/include -I$(RIOTBASE)/core/include -I$(RIOTBASE)/drivers/include -I$(RIOTBASE)/drivers/cc110x_ng/include -I$(RIOTBASE)/cpu/arm_common/include -I$(RIOTBASE)/sys/net/include/
INCLUDES += -I$(RIOTBASE)/sys/net/openwsn/02a-MAClow
INCLUDES += -I$(RIOTBASE)/sys/net/openwsn/02b-MAChigh
INCLUDES += -I$(RIOTBASE)/sys/net/openwsn/03a-IPHC
INCLUDES += -I$(RIOTBASE)/sys/net/openwsn/03b-IPv6
INCLUDES += -I$(RIOTBASE)/sys/net/openwsn/04-TRAN
INCLUDES += -I$(RIOTBASE)/sys/net/openwsn/cross-layers

DIRS =
#DIRS += stupidmac

all:
	@for i in $(DIRS) ; do "$(MAKE)" -C $$i ; done ;

include $(RIOTBASE)/Makefile.base

# remove compilation products
clean::
	@for i in $(DIRS) ; do "$(MAKE)" -C $$i clean ; done ;
	