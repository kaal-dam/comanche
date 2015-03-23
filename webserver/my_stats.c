#include <semaphore.h>
#include <string.h>
#include "my_stats.h"
#include "message.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "my_semaphore.h"


/*stats du serveur en variable globale mais accessible uniquement depuis my_stats.c*/
static web_stats* stats;

/*met tous les attributs de la variable globale web_stats a 0*/
int init_stats(){
    void* mm;
    /*creation d'une zone de memoire partagee pour les stats*/
    mm=mmap(NULL, sizeof(web_stats), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    if(mm==MAP_FAILED){
        perror("mmap stats");
        return -1;
    }
    stats=mm;
    /*init des stats a zero*/
    stats->served_connections=0;
    stats->served_requests=0;
    stats->ok_200=0;
    stats->ko_400=0;
    stats->ko_403=0;
    stats->ko_404=0;
    return 1;
}

/*renvoie les stats au client*/
void send_stats(FILE *client){
    char s[2048];
    int nb_ecrits=0;
    if((nb_ecrits=sprintf(s, "statistiques du serveur:\n\nserved_connections: %d\r\nserved_requests: %d\r\nok_200: %d\r\nko_400: %d\r\nko_403: %d\r\nko_404: %d\r\n\r\n", stats->served_connections, stats->served_requests, stats->ok_200, stats->ko_400, stats->ko_403, stats->ko_404))<1){
        printf("erreur de creation de la chaine des stats");
        fflush(NULL);
        exit(-1);
    }
    send_response(client, 200, "OK", s);
}

/*renvoie un pointeur vers la variable web_stats*/
web_stats * get_stats (void){
    return stats;      
}
