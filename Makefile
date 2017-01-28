all: sxmp

sxmp: sxmp.o libao.o xmp.o ncurses.o
	gcc -o sxmp sxmp.o libao.o xmp.o ncurses.o -lxmp -lao -lncurses

sxmp.o:
	gcc -c sxmp.c

libao.o:
	gcc -c audio/libao.c

xmp.o:
	gcc -c player/xmp.c

ncurses.o:
	gcc -c ui/ncurses.c

clean:
	rm *.o
	rm sxmp
