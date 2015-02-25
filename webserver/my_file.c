#include "my_file.h"


int check_and_open(const char *url, const char *document_root){
    int fdFile;
    char tmp[512];
    strcpy(tmp,document_root);
    strcat(tmp,url);
    
    if(open(document_root,O_RDONLY)!=-1){
        if((fdFile=open(tmp,O_RDONLY))!=-1){
            return fdFile;
        }
        else{
            perror("open file");
            return -1;
        }
    }
    else{
        perror("open root");
        return -1;
    }
    
}
