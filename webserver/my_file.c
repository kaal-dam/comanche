#include "my_file.h"

/*verifie que l'url et le document root menent vers un fichier existant et retourne le descripteur vers ce fichier (ouvert), ou -1 en cas d'erreur*/
int check_and_open(const char *url, const char *document_root){
    int fdFile;
    /*chemin relatif vers le fichier demande par le client (par concat. du chemin du dossier servi par le serveur et du chemin vers le fichier voulu dans ce dossier)*/
    char path[512];
    struct stat file_stat;
    strcpy(path, document_root);
    /*obtention lien complet vers le fichier demandé par le client*/
    strcat(path, url);
    if(strlen(path)<strlen(url)+strlen(document_root)){
        printf("probleme concat. doc_root et url");
        fflush(NULL);
        return -1;
    }
    /*recuperation des infos sur le fichier indique par path*/
    if(stat(path, &file_stat)!=-1){
        /*Verif que le fichier indique par path est un fichier regulier*/
        if(S_ISREG(file_stat.st_mode)){
            /*Ouverture du fichier pointe par path*/
            if((fdFile=open(path, O_RDONLY))!=-1){   
                return fdFile;
            }else{
                perror("open file");
                return -1;
            }
        }else{
            printf("%s n'est pas un chemin vers un fichier valide!\n", path);
            return -1;
        }
    }else{
        perror("stat");
        return -1;
    }
}

/*retourne la taille du fichier pointe par fd ou -1 en cas d'erreur*/
int get_file_size(int fd){
    struct stat file_stat;
    if(fstat(fd, &file_stat)!=-1){
        return file_stat.st_size;
    }else{
        perror("fstat");
        return -1;
    }
}

/*envoie le contenue du fichier pointe par fd_in sur fd_out qui correspond a la socket cliente et retourne le nombre d'octets ecrits ou -1 si erreur*/
int copy(int fd_in, int fd_out){
    int nb_ecrits=0;
    if(fd_in!=0 && fd_out!=0){
        FILE * in;
        if((in=fdopen(fd_in, "r"))==NULL){
            perror("fdopen in");
            return -1;
        }else{
            FILE * out;
            if((out=fdopen(fd_out, "w"))==NULL){
                perror("fdopen out");
                return -1;
            }else{
                char buf[512];
                int nb_lus;
                while((nb_lus=fread(buf, 1, 512, in))>0){
                    if((nb_ecrits+=fwrite(buf, 1, nb_lus, out))==0){
                        perror("fwrite");
                        return -1;
                    }
                }
                if(fclose(in)==-1){
                    perror("fclose in");
                    return -1;
                }
                if(fclose(out)==-1){
                    perror("fclose out");
                    return -1;
                }
            }
        }
    }
    return nb_ecrits;
}
