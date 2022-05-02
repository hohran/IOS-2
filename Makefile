# File: Makefile
# Author: Jan Hranička
# Project: IOS Projekt 2
# Date: 2. 5. 2022
# FIT VUT

CC = gcc
CFLAGS = -std=gnu99 -Wall -Wextra -Werror -pedantic
EXEC = proj2

all: $(EXEC)

proj2: process.o molecule.o
	$(CC) -pthread $^ -o $@

%.o: %.c molecule.h
	$(CC) -c $(CFLAGS) $<
	
.PHONY: clean zip

clean:
	rm -f *.o proj2*

zip:
	zip proj2.zip *.c *.h Makefile
