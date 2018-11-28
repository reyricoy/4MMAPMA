CC=gcc
CFLAGS= -Wall -O -g -std=c99
LDFLAGS=
EXEC=exec
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

all: $(EXEC)

exec: $(OBJ)
			$(CC) -o $@ $^ $(LDFLAGS)

dico.c: dico.h
%.o: %.c
		$(CC) -o $@ -c $^ $(CFLAGS)

clean:
	rm -f *.o core

mrproper: clean
	rm -f $(EXEC)
