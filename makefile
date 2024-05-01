
EXECUTABLES = \
       bin/test

all: $(EXECUTABLES) 

clean:
	rm -f bin/* 

CC = gcc
CFLAGS = -g -I./Libfdr/include
LDFLAGS = -g


bin/test: src/test.c
	$(CC) $(CFLAGS) -o bin/test src/test.c $(LDFLAGS) Libfdr/obj/fields.o
	


