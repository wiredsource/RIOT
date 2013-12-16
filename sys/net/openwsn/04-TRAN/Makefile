SUBMOD:=$(shell basename $(CURDIR)).a
BINDIR = $(RIOTBASE)/bin/
SRC = $(wildcard *.c)
OBJ = $(SRC:%.c=$(BINDIR)%.o)
DEP = $(SRC:%.c=$(BINDIR)%.d)

INCLUDES += -I$(RIOTBASE) -I$(RIOTBASE)/sys/include -I$(RIOTBASE)/core/include -I$(RIOTBASE)/drivers/include -I$(RIOTBASE)/drivers/cc110x_ng/include -I$(RIOTBASE)/cpu/arm_common/include -I$(RIOTBASE)/sys/net/include/ 
INCLUDES += -I$(RIOTBASE)/sys/net/openwsn/02a-MAClow
INCLUDES += -I$(RIOTBASE)/sys/net/openwsn/02b-MAChigh
INCLUDES += -I$(RIOTBASE)/sys/net/openwsn/03a-IPHC
INCLUDES += -I$(RIOTBASE)/sys/net/openwsn/03b-IPv6
INCLUDES += -I$(RIOTBASE)/sys/net/openwsn/04-TRAN
INCLUDES += -I$(RIOTBASE)/sys/net/openwsn/07-APP/ohlone
INCLUDES += -I$(RIOTBASE)/sys/net/openwsn/07-APP/tcpecho
INCLUDES += -I$(RIOTBASE)/sys/net/openwsn/07-APP/tcpinject
INCLUDES += -I$(RIOTBASE)/sys/net/openwsn/07-APP/tcpprint
INCLUDES += -I$(RIOTBASE)/sys/net/openwsn/07-APP/udpecho
INCLUDES += -I$(RIOTBASE)/sys/net/openwsn/07-APP/udpinject
INCLUDES += -I$(RIOTBASE)/sys/net/openwsn/07-APP/udplatency
INCLUDES += -I$(RIOTBASE)/sys/net/openwsn/07-APP/udpprint
INCLUDES += -I$(RIOTBASE)/sys/net/openwsn/07-APP/udprand
INCLUDES += -I$(RIOTBASE)/sys/net/openwsn/07-APP/udpstorm
INCLUDES += -I$(RIOTBASE)/sys/net/openwsn/cross-layers

.PHONY: $(BINDIR)$(SUBMOD)

$(BINDIR)$(SUBMOD): $(OBJ)
	$(AR) rcs $(BINDIR)$(MODULE) $(OBJ)

# pull in dependency info for *existing* .o files
-include $(OBJ:.o=.d)

# compile and generate dependency info
$(BINDIR)%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(BOARDINCLUDE) $(PROJECTINCLUDE) $(CPUINCLUDE) -c $*.c -o $(BINDIR)$*.o
	$(CC) $(CFLAGS) $(INCLUDES) $(BOARDINCLUDE) $(PROJECTINCLUDE) $(CPUINCLUDE) -MM $*.c > $(BINDIR)$*.d
	@printf "$(BINDIR)" | cat - $(BINDIR)$*.d > /tmp/riot_out && mv /tmp/riot_out $(BINDIR)$*.d

# remove compilation products

clean:
	rm -f $(OBJ) $(DEP)
