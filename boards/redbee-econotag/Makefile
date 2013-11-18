SRC = $(wildcard *.c)
BINDIR = bin/
OBJ = $(SRC:%.c=$(BINDIR)%.o)## defines
DEP = $(SRC:%.c=$(BINDIR)%.d)
export ARCH = $(BOARD)_base.a

INCLUDES += -I$(RIOTBOARD)/redbee-econotag/drivers/include
INCLUDES += -I$(RIOTBOARD)/redbee-econotag/include
INCLUDES += -I$(RIOTBASE)/cpu/arm_common/include
INCLUDES += -I$(RIOTBASE)/cpu/mc1322x/include

.PHONY: $(BINDIR)/$(ARCH)

all: $(BINDIR)$(ARCH)
	$(MAKE) -C drivers

$(BINDIR)$(ARCH): $(OBJ)
	$(AR) rcs $(BINDIR)$(ARCH) $(OBJ)

# pull in dependency info for *existing* .o files
-include $(OBJ:.o=.d)

# compile and generate dependency info
$(BINDIR)%.o: %.c
	mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $(CFLAGS_MTHUMB) $(INCLUDES) $(BOARDINCLUDE) $(PROJECTINCLUDE) $(CPUINCLUDE) -c $*.c -o $(BINDIR)$*.o
	$(CC) $(CFLAGS) $(CFLAGS_MTHUMB) $(INCLUDES) $(BOARDINCLUDE) $(PROJECTINCLUDE) $(CPUINCLUDE) -MM $*.c > $(BINDIR)$*.d
	@printf "$(BINDIR)"|cat - $(BINDIR)$*.d > /tmp/riot_out && mv /tmp/riot_out $(BINDIR)$*.d

# remove compilation products
clean:
<<<<<<< HEAD
	"$(MAKE)" -C drivers clean
	rm -f $(BINDIR)$(ARCH) $(OBJ) $(DEP)
=======
	${MAKE} -C drivers clean
	rm -f $(OBJ) $(DEP)
>>>>>>> fix for the redbee-econotag Makefile to work again
	@if [ -d $(BINDIR) ] ; \
	then rmdir $(BINDIR) ; \
	fi

