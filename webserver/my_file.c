#include "my_file.h"


int check_and_open(const char *url, const char *document_root){
    int fdFile;
    char tmp[512];
    struct stat file_stat;
    strcpy(tmp,document_root);
    strcat(tmp,url);
    
   
       /*recuperation des infos sur le dossier*/
        if(stat(tmp, &file_stat)!=-1){
            /*Verif document_root est un dossier*/
            if(S_ISREG(file_stat.st_mode)){
                if((fdFile=open(tmp,O_RDONLY))!=-1){
                    
                    return fdFile;
                }
                else{
                    perror("open file");
                    return -1;
                }
            }
            else{
                printf("%s n'est pas un fichier valide!\n", url);
                return -1;
            }
        }
        else{
            perror("stat");
            return -1;
        }
    
    
    
}
