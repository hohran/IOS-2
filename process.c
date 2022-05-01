
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
void hydrogen(int idO);

int main(int argc, char* argv[]) {
    
    if(argc != 5) {      //Název programu se počítá do argumentů programu
        fprintf(stderr, "process.c: Program needs exactly 4 arguments (NO, NH, TI, TB)\n");
        exit(1);
    }       //Kontrola počtu argumentů programu


    if(arg_to_int(argv[1], &NO)) { exit(1); }       //Kontrola načtení argumentu NO
    if(arg_to_int(argv[2], &NH)) { exit(1); }       //Kontrola načtení argumentu NH
    if(arg_to_int(argv[3], &TI)) { exit(1); }       //Kontrola načtení argumentu TI
    if(arg_to_int(argv[4], &TB)) { exit(1); }       //Kontrola načtení argumentu TB

    if(TI > 1000) {
        fprintf(stderr, "process.c: Argument \'TI\' cannot be greater than 1000\n");
        exit(1);
    }       //Kontrola velikosti TI

    if(TB > 1000) {
        fprintf(stderr, "process.c: Argument \'TB\' cannot be greater than 1000\n");
        exit(1);
    }       //Kontrola velikosti TB

    setbuf(stdin, NULL);



    for(int i = 1; i <= NO; i++) {

        pid_t id = fork();
        if(id == 0) {
            oxygen(i);
        }       //Potomek
    }       //Vytvoření všech O

    for(int i = 1; i <= NH; i++) {

        pid_t id = fork();
        if(id == 0) {
            hydrogen(i);
        }       //Potomek
    }       //Vytvoření všech H
    
    while(wait(NULL) > 0);      //Počkání na ukončení všech ostatních procesů
    printf("Konec\n");
}

void oxygen(int idO) {
    printf("O %d: started\n", idO);

    rand_sleep(TI);       //Uspání na <0,TI> milisekund

    printf("O %d: going to queue\n", idO);

    exit(0);
}       //Proces kyslíku

void hydrogen(int idH) {
    printf("H %d: started\n", idH);

    exit(0);
}       //Proces vodíku