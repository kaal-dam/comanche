#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "socket.h"
#include "my_signal.h"
#include "son.h"
#include "my_stats.h"
#include "my_semaphore.h"

int main(){
    struct stat file_stat;
    /*repertoire racine du serveur*/
    const char *document_root="../resources";
    /*recuperation des infos sur le fichier contenu dans document root*/
    if(stat(document_root, &file_stat)!=-1){
        /*Verif lien fourni dans document_root est un dossier existant*/
        if(S_ISDIR(file_stat.st_mode)){
            /*verif droit lecture sur le dossier fourni dans document_root*/
            if(access(document_root, R_OK | X_OK)==0){
                /*document_root ok, init des stats et de la semaphore, creation serveur*/
                initialiser_signaux();
		        int serveur = creer_serveur(8080);
                /*initialisation stats du serveur*/
                if(init_stats()!=1){
                    printf("erreur init_stats, arret programme\n");
                    fflush(NULL);
                    return -1;
                }
                /*initialisation de la semaphore*/
                if(init_my_semaphore()!=0){
                    printf("erreur init_my_semaphore, arret du programme\n");
                    fflush(NULL);
                }
                /*serveur correctement créé?*/
		        if(serveur == -1){
		            printf("erreur de creation serveur\n");
		            fflush(stdout);
		            return -1;
		        }
		        /*accepter les connexions indefiniment*/
		        while(1){
		            /*descripteur de fichier correspondant a la socket cliente*/
		            int client;
		            /*Attente d'une connexion client (bloquant)*/
		            client=accept(serveur, NULL, NULL);
		            if(client==-1){
		                perror("connection to server fail");
		                return -1;
		            }else{
                        /*client connecte*/
                        /*passage semaphore sur wait*/
                        sem_t *sem=get_my_semaphore();
                        if(sem_wait(sem)==-1){
                            perror("sem_wait");
                            return -1;
                        }
                        /*incrementation nombre de connexions servies*/
                        get_stats()->served_connections+=1;
                        /*passage semaphore sur post*/
                        if(sem_post(sem)==-1){
                            perror("sem_post");
                            return -1;
                        }
                        /*fork du process pour traiter le client dans un fils sans bloquer l'acceptation d'autres clients*/
		                int pid=fork();
		                /*fork foire*/
		                if(pid==-1){
		                    perror("fork");
		                    return -1;
		                }
		                /*Dans le process fils*/
		                if(pid==0){
                            /*fonction qui s'occupe du process fils*/
		                    traitement_fils(client, document_root);
		                }else{
		                    /*Dans le pere, on ferme le descripteur client qui ne sert pas dans le pere*/
		                    close(client);
		                }
		            }
		        }
            }else{
                perror("access");
                return -1;
            }
        }else{
            printf("%s n'est pas un repertoire valide! arret du serveur\n", document_root);
            return -1;
        }
    }else{
        printf("le repertoire %s n'existe pas! arret du serveur\n", document_root);
        fflush(NULL);
        perror("stat");
        return -1;
    }
}
