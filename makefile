
EXECUTABLES = \
       bin/test

all: $(EXECUTABLES) 

clean:
	rm -f bin/* 

CC = gcc
CFLAGS = -g -I ./Libfdr/include -I./include
LDFLAGS = -g


bin/test: src/test.c src/komut.c
	$(CC) $(CFLAGS) -o bin/test src/test.c src/komut.c $(LDFLAGS) Libfdr/obj/fields.o




