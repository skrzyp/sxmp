CC = gcc
CFLAGS = -W -Werror -Wall -Wpedantic -std=c99 -D_POSIX_C_SOURCE -fPIC -s -O3
LDFLAGS = -lao -lncurses
SHAREFLAGS = -shared
all: sxmp sxmp-asap
	rm *.o
	mv *.so libs/

sxmp: sxmp.o audio_libao.so player_xmp.so ui_ncurses.so
	${CC} ${CLFAGS} ${LDFLAGS} -o sxmp sxmp.o -L. -l:audio_libao.so -l:player_xmp.so -l:ui_ncurses.so

sxmp-asap: player_asap.so
	${CC} ${CLFAGS} -o sxmp-asap sxmp.o \
	-L. -l:audio_libao.so -l:ui_ncurses.so -l:player_asap.so \
	-L../asap-3.2.0/ -l:asap.so

sxmp.o:
	${CC} ${CFLAGS} -c sxmp.c

asap.so:
	${CC} ${CFLAGS} -c 3rdparty/asap/asap.c
	${CC} ${SHAREFLAGS} -o asap.so asap.o

player_asap.so: asap.so
	${CC} ${CFLAGS} -c player/asap.c
	${CC} ${SHAREFLAGS} -o player_asap.so asap.o -L. -l:asap.so

audio_libao.so:
	${CC} ${CFLAGS} -c audio/libao.c
	${CC} ${SHAREFLAGS} -o audio_libao.so libao.o -lao

player_xmp.so:
	${CC} ${CFLAGS} -c player/xmp.c
	${CC} ${SHAREFLAGS} -o player_xmp.so xmp.o -lxmp

ui_ncurses.so:
	${CC} ${CFLAGS} -c ui/ncurses.c
	${CC} ${SHAREFLAGS} -o ui_ncurses.so ncurses.o -lncurses

clean:
	@rm *.o
	@rm libs/*.so
	@rm sxmp
