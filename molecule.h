// Soubor: molecule.h
// Autor: Jan Hranička
// Projekt: IOS Projekt 2
// Fakulta: FIT VUT

#ifndef MOLECULE_H
#define MOLECULE_H

#include <stdio.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

enum VAL {NO = 1, NH, TI, TB, SIZE};
unsigned val[SIZE];


int arg_to_int(char* str, unsigned* val);

#endif

/*** Konec souboru molecule.h ***/