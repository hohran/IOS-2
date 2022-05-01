
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
    
    if(load_args(argc, argv)) {
        exit(1);
    }

    setbuf(stdin, NULL);

    line_count = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    sem_init(line_count, 1, 1);

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