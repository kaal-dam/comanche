#include "message.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Renvoie le code et statut correspondant a la requete faite par le client*/
void send_status(FILE * client, int code, const char * reason_phrase){
    if(fprintf(client, "HTTP/1.1 %d %s\r\n", code, reason_phrase)<0){
        exit(-1);
    }
}

/*Renvoie le message complet correspondant a la requete (non valide pour raison x) du client (code et statut + options reponse HTTP et message*/
void send_response(FILE * client, int code, const char * reason_phrase, const char * message_body){
    send_status(client, code, reason_phrase);
    if(fprintf(client, "Connection: close\r\nContent-Type: %s\r\nContent-Length: %lu\r\n\r\n%d %s", "text/plain", strlen(message_body)+4, code, message_body)<0){
        exit(-1);
    }
}

/*Renvoie le message complet au client comme au dessus, mais pas les donnees car on s'en occupera juste apres avec la fonction copy*/
void send_response_file(FILE * client, int code, const char * reason_phrase, int size, char * mime_type){
    send_status(client, code, reason_phrase);
    if(fprintf(client, "Connection: close\r\nContent-Type: %s\r\nContent-Length: %d\r\n\r\n", mime_type, size)<0){
        exit(-1);
    }
    fflush(NULL);
}
