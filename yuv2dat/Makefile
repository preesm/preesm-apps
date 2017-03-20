
CC=gcc
CCWIN=x86_64-w64-mingw32-gcc
CFLAGS=-O2 -fPIC -static -Wall -Wextra
INCLUDES=-I./include/

all: yuv2dat yuv2dat.exe

yuv2dat: $(wildcard src/*.c)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

yuv2dat.exe: $(wildcard src/*.c)
	$(CCWIN) $(CFLAGS) $(INCLUDES) $^ -o $@
	
clean:
	rm -f yuv2dat yuv2dat.exe
