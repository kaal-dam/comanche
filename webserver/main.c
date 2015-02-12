#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include "socket.h"
#include "my_signal.h"
#include "son.h"

int main(){
    initialiser_signaux();
    int serveur = creer_serveur(8080);
    if(serveur == -1){
        printf("erreur de creation serveur");
        fflush(stdout);
        return -1;
    }
    /*accepter les connexions indefiniment*/
    while(1){
        /*descripteur de fichier correspondant a la socket cliente*/
        int client;
        client=accept(serveur, NULL, NULL);
        if(client==-1){
            perror("connection to server fail");
            return -1;
        }else{
            int pid=fork();
            /*fork foire*/
            if(pid==-1){
                perror("fork");
                return -1;
            }
            /*Dans le process fils*/
            if(pid==0){
                traitement_fils(client);
            }else{
                /*Dans le pere*/
                close(client);
            }
        }
    }
}
