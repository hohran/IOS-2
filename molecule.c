/**
 * @file molecule.c
 * @author Jan Hranička
 * @brief Functions for creating molecules
 * @date 2022-04-30
 * 
 * FIT VUT
 */


#include "molecule.h"



int str_to_int(char* str, int* val) {
    char *p;        //Storage of excess characters

    if(str[0] == '\0') { 
        fprintf(stderr, "str_to_int: Program argument must be specified\n");
        return -1; 
    }               //Empty argument

    *val = strtol(str, &p, 10);

    if(errno != 0 || *p != 0 || *val < 0) {
        fprintf(stderr, "str_to_int: Program argument must be a natural number\n");
        return 1;
    }               //Failure of strtol or non digit characters in str
    
    return 0;
}



int load_args(int argc, char* argv[]){
    if(argc != 5) {      //Program name counts as an argument
        fprintf(stderr, "load_args: Program needs exactly 4 arguments (NO, NH, TI, TB)\n");
        return -1;
    }       //Check if we have the correct number of arguments

    if(str_to_int(argv[1], NO)) { return 1; }       //Check if NO is loaded correctly
    if(str_to_int(argv[2], NH)) { return 1; }       //Check if NH is loaded correctly
    if(str_to_int(argv[3], &TI)) { return 1; }       //Check if TI is loaded correctly
    if(str_to_int(argv[4], &TB)) { return 1; }       //Check if TB is loaded correctly

    if(*NO == 0) {
        fprintf(stderr, "load_args: Argument \'NO\' cannot be 0 (specified on forum)\n");
        return 2;
    }               //There is no sense in having 0 oxygens

    if(*NH == 0) {
        fprintf(stderr, "load_args: Argument \'NH\' cannot be 0 (specified on forum)\n");
        return 2; 
    }               //There is no sense in having 0 hydrogens

    if(TI > 1000) {
        fprintf(stderr, "load_args: Argument \'TI\' cannot be greater than 1000\n");
        return 2;
    }               //Too large TI

    if(TB > 1000) {
        fprintf(stderr, "load_args: Argument \'TB\' cannot be greater than 1000\n");
        return 2;
    }               //Too large TB

    return 0;
}



void rand_sleep(int max) {
    time_t seed;
    srand(time(&seed));         //Added randomness
    usleep( (rand() % (max + 1)) * 1000 );
}



void print_report(const char *mess, ...) {

    va_list pr_arg;
    va_start(pr_arg, mess);         //Arguments start with mess

    sem_wait(mutex_line);

    (*A)++;
    fprintf(fp, "%d: ", *A);

    vfprintf(fp, mess, pr_arg);             //Printing to fp

    sem_post(mutex_line);

    va_end(pr_arg);

}

void create(int num, void (*process)(id_t elem)) {
    
    for(int i = 1; i <= num; i++) {

        pid_t id = fork();
        if(id == 0) {
            process(i);
        }                                   //Child process
        if(id == -1) {
            perror("create");
            exit(1);
        }                                   //Unwanted child process
    }                           //Do this (num)times
}


int setup() {

    fp = fopen("proj2.out", "w");           //Filename from the task
    if(fp == NULL) {
        perror("setup");
        exit(1);
    }                               //If fopen failed

    setbuf(fp, NULL);               //Stops prints to this file from buffering (to keep the correct order)
    

    #define DO_MAP(type, var) do {  \
        var = mmap(NULL, sizeof(type), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);   \
        if(var == MAP_FAILED) {     \
            perror("setup");        \
            return 1;               \
        }       \
    } while(0)                      //Same process for all the mmapping

    #define DO_INIT(name, val) do { \
        if(sem_init(name, 1, val) == -1) {  \
            perror("setup");        \
            return 2;               \
        }   \
    } while(0)                      //Same process for initializing all the semaphores


    DO_MAP(int, NO);
    DO_MAP(int, NH);
    DO_MAP(int, A);
    DO_MAP(int, noM);
    DO_MAP(int, mols);

    DO_MAP(sem_t, mutex_line);
    DO_MAP(sem_t, oxy_start);
    DO_MAP(sem_t, oxy_end);
    DO_MAP(sem_t, hydro_start);
    DO_MAP(sem_t, hydro_end);
    DO_MAP(sem_t, mutex_mol);
    DO_MAP(sem_t, sigO);
    DO_MAP(sem_t, sigH);

    DO_INIT(mutex_line, 1);
    DO_INIT(oxy_start, 0);
    DO_INIT(oxy_end, 0);
    DO_INIT(hydro_start, 0);
    DO_INIT(hydro_end, 0);
    DO_INIT(mutex_mol, 1);
    DO_INIT(sigO, 0);
    DO_INIT(sigH, 0);
        

   return 0;
}



void cleanup() {
    
    int err = 0;

    #define UN_MAP(type, var) err += munmap(var, sizeof(type))

    #define DO_DESTROY(name) err += sem_destroy(name)

    UN_MAP(int, NO);
    UN_MAP(int, NH);
    UN_MAP(int, A);
    UN_MAP(int, noM);
    UN_MAP(int, mols);

    DO_DESTROY(mutex_line);
    DO_DESTROY(oxy_start);
    DO_DESTROY(oxy_end);
    DO_DESTROY(hydro_start);
    DO_DESTROY(hydro_end);
    DO_DESTROY(mutex_mol);
    DO_DESTROY(sigO);
    DO_DESTROY(sigH);

    UN_MAP(sem_t, mutex_line);
    UN_MAP(sem_t, oxy_start);
    UN_MAP(sem_t, oxy_end);
    UN_MAP(sem_t, hydro_start);
    UN_MAP(sem_t, hydro_end);
    UN_MAP(sem_t, mutex_mol);
    UN_MAP(sem_t, sigO);
    UN_MAP(sem_t, sigH);

    if(err) {
        perror("cleanup\n");
        exit(1);
    }       //If any of the functions failed
}

void mol_inc() {
    sem_wait(mutex_mol);
    (*noM)++;
    sem_post(mutex_mol);
}

int mol_count(int O, int H) {
    if(2*O > H) return H/2;
    else return O;
}

void release() {

    int excess_oxy = *NO - *noM;            //Count oxygens that won't be part of a molecule
    int excess_hydro = *NH - 2*(*noM);      //Count hydrogens that won't be part of a molecule

    mol_inc();              //Increment noM so that the following molocule processes will fail

    for(int i = 0; i < excess_oxy; i++) {
        sem_post(oxy_start);
    }                       //Release all oxygens

    for(int i = 0; i < excess_hydro; i++) {
        sem_post(hydro_start);
    }                       //Release all oxygens

}

void merge_mol() {
    mol_inc();

    sem_post(oxy_start);
    sem_post(hydro_start);
    sem_post(hydro_start);

    sem_post(oxy_end);
    sem_wait(hydro_end);
    sem_wait(hydro_end);
}
