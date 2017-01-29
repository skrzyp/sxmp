CC = gcc
CFLAGS = -W -Werror -Wall -Wpedantic -std=c99 -D_POSIX_C_SOURCE
LDFLAGS = -lao -lncurses
all: sxmp sxmp-asap

sxmp: sxmp.o libao.o xmp.o ncurses.o
	${CC} ${CLFAGS} ${LDFLAGS} -lxmp -o sxmp sxmp.o libao.o xmp.o ncurses.o

sxmp-asap: sxmp.o libao.o asap.o ncurses.o
	${CC} ${CFLAGS} ${LDFLAGS} -o sxmp-asap sxmp.o libao.o asap.o ncurses.o \
	-Wl,-whole-archive -lasap -Wl,-no-whole-archive

asap.o:
	${CC} ${CFLAGS} -c player/asap.c

sxmp.o:
	${CC} ${CFLAGS} -c sxmp.c

libao.o:
	${CC} ${CFLAGS} -c audio/libao.c

xmp.o:
	${CC} ${CFLAGS} -c player/xmp.c

ncurses.o:
	${CC} ${CFLAGS} -c ui/ncurses.c

clean:
	@rm *.o
	@rm sxmp
	@rm sxmp-asap
