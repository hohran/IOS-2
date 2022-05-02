#ifndef MOLECULE_H
#define MOLECULE_H

/**
 * @file molecule.h
 * @author Jan Hranička
 * @brief process.c interface
 * @date 2022-05-02
 * 
 * FIT VUT
 */

#include <stdio.h>          //Working with files and prints
#include <semaphore.h>      //Semaphores
#include <sys/mman.h>       //Shared memory
#include <sys/types.h>      //fork()
#include <unistd.h>         //fork() and usleep()
#include <stdlib.h>         //Rand and strtol()
#include <errno.h>          //Errno and perror
#include <stdarg.h>         //Custom args in print_report()
#include <time.h>           //Randomness in rand_sleep()


int *NO;    /* Number of oxygens */
int *NH;    /* Number of hydrogens */
int TI;     /* Max time for elements before going to queue */
int TB;     /* Max time for elements before creating molecule */

FILE* fp;   /* File for printing reports */

int* A;     /* Line counter */

int* noM;   /* Counter of created molecules */

int* mols;  /* Precalculated number of molecules */


/* Value incrementation */
sem_t* mutex_line;      /* For incrementing A */
sem_t* mutex_mol;       /* For incrementing noM */

/* Main process -- Element process */
sem_t* oxy_start;       /* Oxygen started creating molecule */
sem_t* oxy_end;         /* Oxygen ended creating molecule */
sem_t* hydro_start;     /* Hydrogen started creating molecule */
sem_t* hydro_end;       /* Hydrogen ended creating molecule */

/* Element process -- Element process */
sem_t* sigO;            /* Oxygen is prepared for creating molecule */
sem_t* sigH;            /* Oxygen is prepared for creating molecule */


/**
 * @brief Convert program argument to natural number
 * 
 * @param str String to convert from
 * @param val Adress of loaded number
 * @return int 0 for success, 1 for failure
 */
int str_to_int(char* str, int* val);

/**
 * @brief Load all arguments
 * 
 * @param argc Number of arguments
 * @param argv Array of the arguments
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
 * @brief Create multiple processes
 * 
 * @param num Number of processes being made
 * @param process Function of the created process
 */
void create(int num, void (*process)(id_t elem));

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

/**
 * @brief Merges element processes into a molecule
 * 
 */
void merge_mol();

/**
 * @brief Starting process of creating molecule
 * 
 */
void mol_inc();

/**
 * @brief Calculate how many molecules will be created
 * 
 * @param O number of oxygens
 * @param H number of hydrogens
 * @return int number of molecules
 */
int mol_count(int O, int H);

/**
 * @brief Releases atoms that cannot create molecule
 * 
 */
void release();


#endif

/*** End of file molecule.h ***/
