// Soubor: process.c
// Autor: Jan Hranička
// Projekt: IOS Projekt 2
// Fakulta: FIT VUT

#include "molecule.h"

int main(int argc, char* argv[]) {
    
    if(argc != 5) {
        fprintf(stderr, "process.c: Not enough arguments\n");
        exit(1);
    }

    if(arg_to_int(argv[1], &NO)) {
        fprintf(stderr, "process.c: Argument must be a natural number\n");
        exit(1);
    }

    printf("%d\n", NO);
    
}