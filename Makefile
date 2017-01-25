all: sxmp

sxmp: sxmp.o audio/libao.o player/xmp.o
	gcc -o sxmp sxmp.o libao.o xmp.o -lxmp -lao

sxmp.o:
	gcc -c sxmp.c

audio/libao.o:
	gcc -c audio/libao.c

player/xmp.o:
	gcc -c player/xmp.c

clean:
	rm *.o
	rm sxmp
