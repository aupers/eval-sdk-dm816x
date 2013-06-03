#
# EDID configure tool
#

.PHONY: build install clean


BIN			= devmem2

SRCS			= $(BIN).c
OBJS			= $(SRCS:.c=.o)

CFLAGS += $(EXTRA_CFLAGS)

build:
	$(V)$(CC) -c $(CFLAGS) $(SRCS) -o $(OBJS) $(QOUT)
	$(V)$(CC) $(LDFLAGS) -o $(BIN) $(OBJS) $(QOUT)

install: 
	$(V)install -D -m 755 $(BIN) $(FSROOT)/usr/bin/$(BIN) $(QOUT)

clean: 
	$(V)rm -f $(BIN) *.o core *~ $(QOUT)

include $(DEVDIR)/bsp/classes/rrsdk.class
