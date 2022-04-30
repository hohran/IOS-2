
/**
 * @file molecule.c
 * @author Jan Hranička
 * @brief Functions for creating molecules
 * @date 2022-04-30
 * 
 * FIT VUT
 */


#include "molecule.h"

int arg_to_int(char* str, int* val) {
    long new_val;
    char *p;

    new_val = strtol(str, &p, 10);

    if(errno != 0 || *p != 0 || new_val <= 0) {
        fprintf(stderr, "process.c: Program argument must be a natural number\n");
        return 1;
    }

    *val = new_val;
    return 0;
}
