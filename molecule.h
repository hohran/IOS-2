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
#include <time.h>

int *NO;
int *NH;
int TI, TB;
FILE* fp;

int* A;

int* noM;

sem_t* line_count;
sem_t* oxy_stop;
sem_t* hydro_stop;



/**
 * @brief Convert program argument to unsigned int
 * 
 * @param str String to convert from
 * @param val Adress of loaded number
 * @return int 0 for success, 1 for failure
 */
int arg_to_int(char* str, int* val);

/**
 * @brief Load all arguments
 * 
 * @param argc Number of arguments
 * @param argv Array of arguments
 * @return int 0 for success, other value for failure
 */
int load_args(int argc, char* argv[]);

/**
 * @brief Sleep for <0, max> miliseconds
 * 
 * @param max maximal value of slept miliseconds
 */
void rand_sleep(int max);

/**
 * @brief Print report accordingly to the task
 * 
 * @param mess String to be printed
 * @param ... Other arguments (same as in printf)
 */
void print_report(const char *mess, ...);

/**
 * @brief Create oxygen processes
 * 
 * @param num Number of processes being made
 */
void create_oxygen(int num);

/**
 * @brief Create hydrogen processes
 * 
 * @param num Number of processes being made
 */
void create_hydrogen(int num);

/**
 * @brief The process of oxygen
 * 
 * @param idO ID of an specific oxygen
 */
void oxygen(id_t idO);

/**
 * @brief The process of hydrogen
 * 
 * @param idH ID of an specific hydrogen
 */
void hydrogen(id_t idH);

/**
 * @brief Setting up shared memory and initializing semaphores
 * 
 * @return int 0 for success, other value for failure
 */
int setup();

/**
 * @brief Cleaning up after 'setup' function
 * 
 */
void cleanup();


#endif

/*** Konec souboru molecule.h ***/