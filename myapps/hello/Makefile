#
# myapps/hello/Makefile
#

.PHONY: build install clean


BIN			= hello

SRCS			= $(BIN).c
OBJS			= $(SRCS:.c=.o)

CFLAGS += $(EXTRA_CFLAGS)

build:
	$(V)$(CC) -c $(CFLAGS) $(SRCS) -o $(OBJS) $(QOUT)
	$(V)$(CC) $(LDFLAGS) -o $(BIN) $(OBJS) $(QOUT)

install: 
	$(V)install -D -m 755 $(BIN) $(FSROOT)/examples/$(BIN) $(QOUT)

clean: 
	$(V)rm -f $(BIN) *.debug *.o core *~ $(QOUT)

include ../../bsp/classes/rrsdk.class
