#include "request.h"
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
    int ss=0, majversion, minversion;
    char method[32], s4[2048];
    if((ss=sscanf(request_line, "%s %s HTTP/%d.%d %s", method, request->url, &majversion, &minversion, s4))==4){
        if(strcmp(method, "GET")==0){
            request->method=HTTP_GET;
        }else{
            request->method=HTTP_UNSUPPORTED;
            return 0;
        }
        request->major_version=majversion;
        request->minor_version=minversion;
        if(request->major_version!=1 || (request->minor_version!=0 && request->minor_version!=1)){
            return 0;
        }
        rewrite_url(request->url);
        return 1;
    }else{
        return 0;
    }
}

/*traite les autres lignes de la requete http (pour l'instant on les ignores)*/
void skip_headers(FILE * stream_client){
    char poubelle[1024];
    while(strcmp(poubelle, "\r\n")!=0 && strcmp(poubelle, "\n")!=0){
        fgets_or_exit(poubelle, 1024, stream_client);
    }
}

/*reecris l'url que demande le client pour enlever les parametres si elle en contient*/
void rewrite_url(char *url){
    char *s;
    s=strchr(url, '?');
    if(s!=NULL){
       *s='\0';
    }
    if(strcmp(url, "/")==0){
        url=strcat(url, "index.html");
    }
}
