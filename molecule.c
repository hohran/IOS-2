// Soubor: molecule.c
// Autor: Jan Hranička
// Projekt: IOS Projekt 2
// Fakulta: FIT VUT

#include "molecule.h"

int arg_to_int(char* str, unsigned* val) {
    long new_val;
    char *p;

    new_val = strtol(str, &p, 10);

    if(errno != 0 || *p != 0 || new_val <= 0) {
        return 1;
    }

    *val = new_val;
    return 0;
}
