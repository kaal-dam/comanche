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
                const char * mode;
                /*en mode lecture et ecriture*/
                mode="w+";
                char * s;
                char s3[1024];
                FILE * s2=NULL;
                /*obtenir une structure FILE * a partir du descripteur correspondant a la socket client*/
                s2=fdopen(fd, mode);
                if(s2==NULL){
                    perror("fdopen");
                    exit(-1);
                }
                /*Message de bienvenue*/
                s="Bienvenue sur mon serveur aventurier! Serais tu un ennemi des comanches? si tel est le cas, je te conseille de te deconnecter très vite de ce serveur.. sinon, bienvenue a toi dans notre tribu, tu seras notre invite jusqu'a ce que tu decides de couper la connection qui nous lie. Nous t'offrirons tout ce dont tu as besoin, il te suffira de demander. Prends garde, les comanches sont de vieux indiens rusés et ils adorent faire des farces! ne t'etonne pas si certains de tes fichiers disparaissent ou bien si certains fichiers se creent tout seul sur ton ordinateur, ce ne sera jamais rien de mechant tu peux me faire confiance. Si tu as un probleme quelconque, viens donc voir kaal-dam, le chef de notre tribu, il pourra te depanner avec ses super pouvoirs! sinon, contactes maverick, ce vieux bougre n'est jamais loin et en general il est toujours volontaire pour aider! Evites aussi de parler aux comanches qui sont trop vieux comme serveuris qui t'heberge actuellement, il a tendance a repeter betement tout ce qu'on lui dit, et le pire c'est que ça l'amuse..\n";
                /*Boucle while pour tester l'erreur SIGPIPE*/
                //while(1){
                if(fprintf(s2, s)<0){
                    exit(-1);
                }
                s="a";
                //}
                /*tant que le client est connecte, on repete ce qu'il nous envoie*/
                /*Marche pas encore avec fgets, remplacer la condition while (toujours vrai)*/
                while(feof(s2)!=1){
                    if(fgets(s3, 1024, s2)==NULL){
                        printf("erreur fgets\n");
                        fflush(NULL);
                    }
                    if(fprintf(stdout, s3)<0){
                        printf("erreur fprintf\n");
                        fflush(NULL);
                    }
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
