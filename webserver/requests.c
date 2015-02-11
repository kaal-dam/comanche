#include "requests.h"
#include <string.h>
#include <stdlib.h>

/*lis une ligne de la requete envoyee par le client*/
char *fgets_or_exit(char * buff, int size, FILE *stream){
    if(fgets(buff, size, stream)==NULL){
        exit(-1);
    }
    return buff;
}

/*traite la premiere ligne d'une requete http envoyee par le client, stocke les infos de cette requete dans une structure de type http_request*/
int parse_http_request(const char * request_line, http_request *request){
    int ss=0;
    char s1[32], s2[1024], s3[20], s4[2048];
    if((ss=sscanf(request_line, "%s %s %s %s", s1, s2, s3, s4))==3 && (strcmp(s3, "HTTP/1.0")==0 || strcmp(s3, "HTTP/1.1")==0)){
        if(strcmp(s1, "GET")==0){
            request->method=HTTP_GET;
        }else{
            request->method=HTTP_UNSUPPORTED;
        }
        request->url=s2;
        if(strcmp(s3, "HHTTP/1.0")==0){
            request->minor_version=1;
            request->major_version=0;
        }else if(strcmp(s3, "HTTP/1.1")==0){
            request->major_version=1;
            request->minor_version=0;
        }
        return 1;
    }else{
        return 0;
    }
}

/*traite les autres lignes de la requete http (pour l'instant on les ignores)*/
void skip_headers(FILE * client){
    char poubelle[1024];
    while(strcmp(poubelle, "\r\n")!=0 && strcmp(poubelle, "\n")!=0){
        fgets_or_exit(poubelle, 1024, client);
    }
}
