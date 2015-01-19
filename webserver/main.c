#include <stdio.h>
#include <string.h>
#include "socket.h"
int main(int argc, char ** argv){
    int serveur = cree_serveur(8000);
    if(serveur == -1){
        printf("erreur de creation serveur");
        fflush(stdout);
        return -1;
    }
    /*
     *faire la partie socket client
     */
    return 0;
}
