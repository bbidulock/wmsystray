include ../Rules.make

CC = gcc
CFLAGS = ${X11CFLAGS} -DTRACE_LEVEL=${TRACE_LEVEL} -I../xembed -Wall -g
LDFLAGS = ${X11LDFLAGS} -lXpm

OBJS = main.o ui.o systray.o xpms.o
XEMBED_OBJS = ../xembed/xembed.o

wmsystray: ${OBJS} ${XEMBED_OBJS}
	gcc ${OBJS} ${XEMBED_OBJS} -o wmsystray ${LDFLAGS}

clean:
	rm -f wmsystray ${OBJS}
