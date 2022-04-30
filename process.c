
/**
 * @file process.c
 * @author Jan Hranička
 * @brief Process of creating molecules
 * @date 2022-04-30
 * 
 * FIT VUT
 */

#include "molecule.h"
#include <wait.h>

void oxygen(int idO);

int main(int argc, char* argv[]) {
    
    if(argc != 5) {      //Název programu se počítá do argumentů programu
        fprintf(stderr, "process.c: Program needs exactly 4 arguments (NO, NH, TI, TB)\n");
        exit(1);
    }       //Kontrola počtu argumentů programu


    if(arg_to_int(argv[1], &NO)) {
        exit(1);
    }       //Kontrola načtení argumentu NO

    if(arg_to_int(argv[2], &NH)) {
        exit(1);
    }       //Kontrola načtení argumentu NH

    if(arg_to_int(argv[3], &TI)) {
        exit(1);
    }       //Kontrola načtení argumentu TI

    if(TI > 1000) {
        fprintf(stderr, "process.c: Argument \'TI\' cannot be greater than 1000\n");
        exit(1);
    }

    if(arg_to_int(argv[4], &TB)) {
        exit(1);
    }       //Kontrola načtení argumentu TB

    if(TB > 1000) {
        fprintf(stderr, "process.c: Argument \'TB\' cannot be greater than 1000\n");
        exit(1);
    }


    for(int i = 1; i <= NO; i++) {

        pid_t id = fork();
        if(id == 0) {
            oxygen(i);
        }       //Potomek
    }
    
    while(wait(NULL) > 0);      //Počkání na ukončení všech ostatních procesů
    printf("Konec\n");
}

void oxygen(int idO) {
    printf("O %d: hlasi se\n", idO);

    exit(0);
}