#include "request.h"
#include <string.h>
#include <stdlib.h>

/*lis une ligne de la requete envoyee par le client sur size et renvoie la ligne lue*/
char *fgets_or_exit(char * buff, int size, FILE *stream){
    if(fgets(buff, size, stream)==NULL){
        exit(-1);
    }
    return buff;
}

/*traite la premiere ligne d'une requete http envoyee par le client, stocke les infos de cette requete dans une structure de type http_request. Renvoie 1 si ok et 0 si erreur*/
int parse_http_request(const char * request_line, http_request *request){
    int ss=0, majversion, minversion;
    char method[32], s4[2048];
    /*recuperation de la methode, du chemin, de la partie majeure de la version utilisee ainsi que la partie mineure + verification que pas plus d'elements transmis dans la requete par le client*/
    if((ss=sscanf(request_line, "%s %s HTTP/%d.%d %s", method, request->url, &majversion, &minversion, s4))==4){
        /*si la methode est get*/
        if(strcmp(method, "GET")==0){
            request->method=HTTP_GET;
        /*autres cas (ici un seul, on ne supporte que get*/
        }else{
            request->method=HTTP_UNSUPPORTED;
            return 0;
        }
        request->major_version=majversion;
        request->minor_version=minversion;
        /*verification version ok (1.1 ou 1.0)*/
        if(request->major_version!=1 || (request->minor_version!=0 && request->minor_version!=1)){
            return 0;
        }
        /*reecriture de l'url demandee par le client*/
        rewrite_url(request->url);
        return 1;
    }else{
        return 0;
    }
}

/*traite les autres lignes de la requete http (pour l'instant on les ignores)*/
void skip_headers(FILE * stream_client){
    char poubelle[1024];
    /*tant que la ligne lue n'est pas une ligne vide*/
    while(strcmp(poubelle, "\r\n")!=0 && strcmp(poubelle, "\n")!=0){
        /*lire ou sortir en cas d'erreur*/
        fgets_or_exit(poubelle, 1024, stream_client);
    }
}

/*reecris l'url que demande le client pour enlever les parametres si elle en contient et transformer / en /index.html*/
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
