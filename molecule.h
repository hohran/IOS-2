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
#include <stdarg.h>

int NO, NH, TI, TB;
FILE* fp;

typedef struct semaphores
{
    sem_t* line_count;
}sem_pack;



/**
 * @brief Convert program argument to unsigned int
 * 
 * @param str String to convert from
 * @param val Adress of loaded number
 * @return int 0 for success, 1 for failure
 */
int arg_to_int(char* str, int* val);

/**
 * @brief Sleep for <0, max> miliseconds
 * 
 * @param max maximal value of slept miliseconds
 */
void rand_sleep(int max);

void print_report(const char *mess, ...);



#endif

/*** Konec souboru molecule.h ***/