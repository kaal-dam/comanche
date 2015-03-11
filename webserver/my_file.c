#include "my_file.h"


int check_and_open(const char *url, const char *document_root){
    int fdFile;
    char tmp[512];
    struct stat file_stat;
    strcpy(tmp,document_root);
    strcat(tmp,url);
    if(strlen(tmp)<strlen(url)+strlen(document_root)){
        printf("prob longueur");
        fflush(NULL);
        return -1;
    }
    /*recuperation des infos sur le dossier*/
    if(stat(tmp, &file_stat)!=-1){
        /*Verif document_root est un dossier*/
        if(S_ISREG(file_stat.st_mode)){
            if((fdFile=open(tmp,O_RDONLY))!=-1){   
                return fdFile;
            }else{
                perror("open file");
                return -1;
            }
        }else{
            printf("%s n'est pas un fichier valide!\n", tmp);
            return -1;
        }
    }else{
        perror("stat");
        return -1;
    }
}

int get_file_size(int fd){
    struct stat file_stat;
    if(fstat(fd, &file_stat)!=-1){
        return file_stat.st_size;
    }else{
        perror("fstat");
        return -1;
    }
}

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
