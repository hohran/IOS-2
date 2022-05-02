/**
 * @file process.c
 * @author Jan Hranička
 * @brief Process of creating molecules
 * @date 2022-04-30
 * 
 * FIT VUT
 */

#include "molecule.h"       //Custom library
#include <wait.h>           //wait()


int main(int argc, char* argv[]) {

    if(setup()) {
        cleanup();
        exit(1);
    }       //If setup failed there's no need to continue
    
    if(load_args(argc, argv)) {
        cleanup();
        exit(1);
    }       //If loading arguments failed there's no need to continue

    *mols = mol_count(*NO, *NH);

    create(*NO, oxygen);
    create(*NH, hydrogen);


    for(int i = 0; i < *mols; i++) {
        merge_mol();                            //Merge waiting elements into a molecule
    }                                           //^--(mols)times

    release();
    
    while(wait(NULL) > 0);      //Počkání na ukončení všech ostatních procesů

    cleanup();
    exit(0);        //Success YAY!
}       //The main process

void oxygen(id_t idO) {

    print_report("O %d: started\n", idO);

    rand_sleep(TI);

    print_report("O %d: going to queue\n", idO);

    sem_wait(oxy_start);        //Wait for creation of the next molecule

    if(*noM > *mols) {
        print_report("O %d: not enough H\n", idO);
        exit(1);
    }                           //Checking if there is enough atoms to make this molecule 

    print_report("O %d: creating molecule %d\n", idO, *noM);

    rand_sleep(TB);

    sem_wait(sigH);
    sem_wait(sigH);                 //Wait until both hydrogens started creating this molecule

    sem_post(sigO);
    sem_post(sigO);                 //Then tell them it is finished

    print_report("O %d: molecule %d created\n", idO, *noM);

    sem_post(oxy_end);          //The next oxygen is ready to go

    exit(0);
}       //Process of an oxygen

void hydrogen(id_t idH) {
    print_report("H %d: started\n", idH);

    rand_sleep(TI);

    print_report("H %d: going to queue\n", idH);

    sem_wait(hydro_start);      //Wait for creation of the next molecule

    if(*noM > *mols) {
        print_report("H %d: not enough O or H\n", idH);
        exit(1);
    }                          //It is destined for you to fail

    print_report("H %d: creating molecule %d\n", idH, *noM);

    sem_post(sigH);                     //Tell your oxygen that you are ready

    sem_wait(sigO);                     //And wait for him to do the job

    print_report("H %d: molecule %d created\n", idH, *noM);

    sem_post(hydro_end);                //Read the description of hydro_end to understand this complex function

    exit(0);
}       //Process of hydrogen
