
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
    char *p;

    *val = strtol(str, &p, 10);

    if(errno != 0 || *p != 0 || *val <= 0) {
        fprintf(stderr, "process.c: Program argument must be a natural number\n");
        return 1;
    }
    
    return 0;
}



int load_args(int argc, char* argv[]){
    if(argc != 5) {      //Název programu se počítá do argumentů programu
        fprintf(stderr, "process.c: Program needs exactly 4 arguments (NO, NH, TI, TB)\n");
        return -1;
    }       //Kontrola počtu argumentů programu

    if(arg_to_int(argv[1], NO)) { return 1; }       //Kontrola načtení argumentu NO
    if(arg_to_int(argv[2], NH)) { return 1; }       //Kontrola načtení argumentu NH
    if(arg_to_int(argv[3], &TI)) { return 1; }       //Kontrola načtení argumentu TI
    if(arg_to_int(argv[4], &TB)) { return 1; }       //Kontrola načtení argumentu TB

    if(TI > 1000) {
        fprintf(stderr, "process.c: Argument \'TI\' cannot be greater than 1000\n");
        return 2;
    }       //Kontrola velikosti TI

    if(TB > 1000) {
        fprintf(stderr, "process.c: Argument \'TB\' cannot be greater than 1000\n");
        return 2;
    }       //Kontrola velikosti TB

    return 0;
}



void rand_sleep(int max) {
    time_t seed;
    srand(time(&seed));         //Added randomness
    usleep( (rand() % (max + 1)) * 1000 );
}



void print_report(const char *mess, ...) {

    va_list pr_arg;

    va_start(pr_arg, mess);

    sem_wait(line_count);

    (*A)++;
    printf("%d: ", *A);

    vfprintf(stdout, mess, pr_arg);

    sem_post(line_count);

    va_end(pr_arg);

}



void create_oxygen(int num) {

    for(int i = 1; i <= num; i++) {

        pid_t id = fork();
        if(id == 0) {
            oxygen(i);
        }
        if(id == -1) {
            perror("fork");
            exit(1);
        }
    }
}



void create_hydrogen(int num) {

    for(int i = 1; i <= num; i++) {

        pid_t id = fork();
        if(id == 0) {
            hydrogen(i);
        }
        if(id == -1) {
            perror("fork");
            exit(1);
        }
    }
}
