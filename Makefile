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

proj2: mainProcess.o
	$(CC) $^ -o $@

.PHONY: clean zip

clean:
	rm -f *.o

zip:
	zip proj2.zip *.c *.h Makefile