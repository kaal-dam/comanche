#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "socket.h"

/*si le processus pere reçoit le signal SIGCHLD il termine son fils pour que celui ci ne reste pas zombie*/
void traitement_signal(){
    int status;
    if(waitpid(-1, &status, WNOHANG)==-1){
        perror("waitpid");
    }
}

/*Fonction qui sert au serveur a ignorer les signaux SIGPIPE et a ne pas laisser de processus zombies*/
void initialiser_signaux(){
    if(signal(SIGPIPE, SIG_IGN)==SIG_ERR){
        perror("signal");
    }
    struct sigaction sa;
    sa.sa_handler=traitement_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags=(SA_RESTART);
    /*si on recoit un signal SIGCHLD*/
    if(sigaction(SIGCHLD, &sa, NULL)==-1){
        perror("sigaction(SIGCHLD)");
    }
}

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
        int fd;
        fd=accept(serveur, NULL, NULL);
        if(fd==-1){
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
                /*Connexion d'un client, message de bienvenue*/
                char *s, *s2;
                int nb_lus;
                s="Bienvenue sur mon serveur aventurier! Serais tu un ennemi des comanches? si tel est le cas, je te conseille de te deconnecter très vite de ce serveur.. sinon, bienvenue a toi dans notre tribu, tu seras notre invite jusqu'a ce que tu decides de couper la connection qui nous lie. Nous t'offrirons tout ce dont tu as besoin, il te suffira de demander. Prends garde, les comanches sont de vieux indiens rusés et ils adorent faire des farces! ne t'etonne pas si certains de tes fichiers disparaissent ou bien si certains fichiers se creent tout seul sur ton ordinateur, ce ne sera jamais rien de mechant tu peux me faire confiance. Si tu as un probleme quelconque, viens donc voir kaal-dam, le chef de notre tribu, il pourra te depanner avec ses super pouvoirs! sinon, contactes maverick, ce vieux bougre n'est jamais loin et en general il est toujours volontaire pour aider! Evites aussi de parler aux comanches qui sont trop vieux comme serveuris qui t'heberge actuellement, il a tendance a repeter betement tout ce qu'on lui dit, et le pire c'est que ça l'amuse..";
                //while(1){
                if(write(fd, s, strlen(s))==-1){
                    perror("message d'accueil");
                    return -1;
                }
                //}
                /*tant que le client est connecte, on repete ce qu'il nous envoie*/
                while((nb_lus=read(fd, &s2, 512))>0){
                    if(write(fd, &s2, nb_lus)==-1){
                        perror("ecriture");
                        return -1;
                    }
                }
                if(nb_lus<0){
                    perror("lecture");
                    return -1;
                }
                /*fils termine*/
                exit(0);
            /*Dans le pere*/
            }else{
                close(fd);
            }
        }
    }
    return 0;
}
