# Soubor: Makefile
# Autor: Jan Hranička
# Projekt: IOS Projekt 2
# Fakulta: FIT VUT

CC = gcc
CFLAGS = -std=gnu99 -Wall -Wextra -Werror -pedantic
LDFLAGS =
EXEC = proj2
OBJ = objFiles

all: $(EXEC)

proj2: process.o molecule.o
	$(CC) -pthread $^ -o $@ $(LDFLAGS)

%.o: %.c molecule.h
	$(CC) -c $(CFLAGS) $<
	
.PHONY: clean zip

clean:
	rm -f *.o proj2*

zip:
	zip proj2.zip *.c *.h Makefile