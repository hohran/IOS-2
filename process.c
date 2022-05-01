
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

    NO = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    NH = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    line_count = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    sem_init(line_count, 1, 1);

    A = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *A = 0;
    
    if(load_args(argc, argv)) {
        //unmap
        exit(1);
    }

    setbuf(stdout, NULL);

    

    create_oxygen(*NO);
    create_hydrogen(*NH);
    
    while(wait(NULL) > 0);      //Počkání na ukončení všech ostatních procesů
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