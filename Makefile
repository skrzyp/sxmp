CC = gcc
CFLAGS = -W -Werror -Wall -Wpedantic -std=c99 -D_POSIX_C_SOURCE -fPIC
LDFLAGS = -lao -lncurses
SHAREFLAGS = -shared
all: sxmp sxmp-asap
	rm *.o
	mv *.so libs/

sxmp: sxmp.o audio_libao.so player_xmp.so ui_ncurses.so
	${CC} ${CLFAGS} ${LDFLAGS} -o sxmp sxmp.o -L. -l:audio_libao.so -l:player_xmp.so -l:ui_ncurses.so

sxmp-asap: player_asap.o
	${CC} ${CLFAGS} ${LDFLAGS} -o sxmp-asap sxmp.o -L. -l:audio_libao.so -l:ui_ncurses.so \
	player_asap.o -Wl,--whole-archive -lasap -Wl,--no-whole-archive

sxmp.o:
	${CC} ${CFLAGS} -c sxmp.c

player_asap.o:
	${CC} ${CFLAGS} -c player/asap.c
	mv asap.o player_asap.o

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
