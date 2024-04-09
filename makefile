CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99

all: wzip

wzip: wzip.o util.o
	$(CC) $(CFLAGS) -o wzip wzip.o util.o

util.o: util.c
	$(CC) $(CFLAGS) -c util.c

clean:
	rm -f wzip *.o
