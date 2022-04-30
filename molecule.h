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

unsigned NO, NH, TI, TB;

int arg_to_int(char* str, unsigned* val);

#endif

/*** Konec souboru molecule.h ***/