# Soubor: Makefile
# Autor: Jan Hranička
# Projekt: IOS Projekt 2
# Fakulta: FIT VUT

CC = gcc
CFLAGS = -std=gnu99 -Wall -Wextra -Werror -pedantic
LDFLAGS = 
EXEC = proj2

all: $(EXEC)

proj2: process.o
	$(CC) $^ -o $@