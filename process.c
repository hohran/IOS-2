
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


int main(int argc, char* argv[]) {

    if(setup()) {
        cleanup();
        exit(1);
    }
    
    if(load_args(argc, argv)) {
        cleanup();
        exit(1);
    }

    *mols = mol_count(*NO, *NH);

    create(*NO, oxygen);        //Test for H
    create(*NH, hydrogen);


    for(int i = 0; i < *mols; i++) {
        merge_mol();
    }

    release();
    
    while(wait(NULL) > 0);      //Počkání na ukončení všech ostatních procesů

    cleanup();
    exit(0);
}

void oxygen(id_t idO) {

    print_report("O %d: started\n", idO);

    rand_sleep(TI);       //Uspání na <0,TI> milisekund

    print_report("O %d: going to queue\n", idO);

    sem_wait(oxy_start);

    if(*noM > *mols) {
        print_report("O %d: not enough H\n", idO);
        exit(0);
    }

    print_report("O %d: creating molecule %d\n", idO, *noM);

    rand_sleep(TB);

    sem_wait(sigH);
    sem_wait(sigH);

    sem_post(sigO);
    sem_post(sigO);

    print_report("O %d: molecule %d created\n", idO, *noM);

    sem_post(oxy_end);

    exit(0);
}       //Proces kyslíku

void hydrogen(id_t idH) {
    print_report("H %d: started\n", idH);

    rand_sleep(TI);       //Uspání na <0,TI> milisekund

    print_report("H %d: going to queue\n", idH);

    sem_wait(hydro_start);

    if(*noM > *mols) {
        print_report("H %d: not enough O or H\n", idH);
        exit(0);
    }

    print_report("H %d: creating molecule %d\n", idH, *noM);

    sem_post(sigH);

    sem_wait(sigO);

    print_report("H %d: molecule %d created\n", idH, *noM);

    sem_post(hydro_end);

    exit(0);
}       //Proces vodíku