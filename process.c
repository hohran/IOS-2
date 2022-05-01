
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

    setup();

    *A = 0;
    
    if(load_args(argc, argv)) {
        //unmap
        exit(1);
    }

    setbuf(stdout, NULL);

    

    create_oxygen(*NO);
    create_hydrogen(*NH);
    
    while(wait(NULL) > 0);      //Počkání na ukončení všech ostatních procesů

    cleanup();
    printf("Konec\n");
}

void oxygen(id_t idO) {
    print_report("O %d: started\n", *A, idO);

    rand_sleep(TI);       //Uspání na <0,TI> milisekund

    print_report("O %d: going to queue\n", idO);

    

    exit(0);
}       //Proces kyslíku

void hydrogen(id_t idH) {
    print_report("H %d: started\n", idH);

    rand_sleep(TI);       //Uspání na <0,TI> milisekund

    print_report("H %d: going to queue\n", idH);


    exit(0);
}       //Proces vodíku