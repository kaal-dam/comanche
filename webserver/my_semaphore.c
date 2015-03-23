#include "my_semaphore.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>

/*ma semaphore*/
sem_t *semaphore;

/*renvoie un pointeur vers ma semaphore*/
sem_t *get_my_semaphore(){
    return semaphore;
}

/*fonction d'initialisation de la semaphore*/
int init_my_semaphore(){
    /*creation dune zone memoire partagee pour la semaphore*/
    void *mms;
    mms=mmap(NULL, sizeof(sem_t), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    if(mms==MAP_FAILED){
        perror("mmap semaphore");
        return -1;
    }
    semaphore=mms;
    int sem_status;
    if((sem_status=sem_init(semaphore, 1, 1))==-1){
        return -1;
    }
    return 0;
}
