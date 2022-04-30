#ifndef MOLECULE_H
#define MOLECULE_H

/**
 * @file molecule.h
 * @author Jan Hranička
 * @brief process.c interface
 * @date 2022-04-30
 * 
 * FIT VUT
 */

#include <stdio.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

enum VAL {NO, NH, TI, TB, COUNT};    //COUNT je počet argumentů
unsigned val[COUNT - 1];

/**
 * @brief Convert program argument to unsigned int
 * 
 * @param str String to convert from
 * @param val Adress of loaded number
 * @return int 0 for success, 1 for failure
 */
int arg_to_uint(char* str, unsigned* val);

#endif

/*** Konec souboru molecule.h ***/