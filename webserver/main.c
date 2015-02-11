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
                char s3[3124];
                FILE * s2=NULL;
                /*obtenir une structure FILE * a partir du descripteur correspondant a la socket client*/
                s2=fdopen(fd, mode);
                if(s2==NULL){
                    perror("fdopen");
                    exit(-1);
                }
                //compteur de lignes lues
                int lues=0;
                unsigned int tailleLue=0;
                s="a";
                //}
                /*tant que le client est connecte, on recupere ce qu'il envoie*/
                char s4[32], s5[1024], s6[20], s7[2048];
                while(feof(s2)!=1){
                    if(fgets(s3, 3124, s2)==NULL){
                        printf("erreur fgets\n");
                        fflush(NULL);
                    }
                    if(lues==0){
                        int ss=0;
                        //verification ligne 1 entete requete HTTP
                        if((ss=sscanf(s3, "%s %s %s %s", s4, s5, s6, s7))!=3 || strcmp(s4, "GET")!=0 || (strcmp(s6, "HTTP/1.1")!=0 && strcmp(s6, "HTTP/1.0")!=0)){
                            fprintf(s2, "HTTP/1.1 400 Bad Request\r\nConnection: close\r\nContent-Length: %u\r\n\r\n400 Bad Request\r\n", (unsigned) sizeof(s3));
                            fflush(NULL);
                            exit(-1);
                        }else{
                            tailleLue+=(unsigned) sizeof(s3);
                        }
                    }else{
                        if(strcmp(s3, "\r\n")==0 || strcmp(s3, "\n")==0){
                            if(strcmp(s5, "/")==0){
			                    if(fprintf(stdout, "%s 200 OK %u\n", s6, (unsigned) sizeof(s3))<0){
			                        exit(-1);
			                    }
			                    /*Message de bienvenue*/
			                    s="Bienvenue sur mon serveur aventurier! Serais tu un ennemi des comanches? si tel est le cas, je te conseille de te deconnecter très vite de ce serveur.. sinon, bienvenue a toi dans notre tribu, tu seras notre invite jusqu'a ce que tu decides de couper la connection qui nous lie. Nous t'offrirons tout ce dont tu as besoin, il te suffira de demander. Prends garde, les comanches sont de vieux indiens rusés et ils adorent faire des farces! ne t'etonne pas si certains de tes fichiers disparaissent ou bien si certains fichiers se creent tout seul sur ton ordinateur, ce ne sera jamais rien de mechant tu peux me faire confiance. Si tu as un probleme quelconque, viens donc voir kaal-dam, le chef de notre tribu, il pourra te depanner avec ses super pouvoirs! sinon, contactes maverick, ce vieux bougre n'est jamais loin et en general il est toujours volontaire pour aider! Evites aussi de parler aux comanches qui sont trop vieux comme serveuris qui t'heberge actuellement, il a tendance a repeter betement tout ce qu'on lui dit, et le pire c'est que ça l'amuse..\n";
			                    /*Boucle while pour tester l'erreur SIGPIPE*/
			                    //while(1){
			                    /*Message de bienvenue*/
			                    if(fprintf(s2, s)<0){
			                        exit(-1);
			                    }
                            }else{
                                if(fprintf(s2, "404 page %s not found\n", s5)<0){
                                    exit(-1);
                                }
                            }
                            exit(0);
                        }else{
                            tailleLue+=(unsigned) sizeof(s3);
                        }
                    }
                    lues++;
                    /*affichage des donnees recues sur le serveur*/
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
