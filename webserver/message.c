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

/*Renvoie le message complet correspondant a la requete du client (code et statut + longueur et message*/
void send_response(FILE * client, int code, const char * reason_phrase, const char * message_body){
    send_status(client, code, reason_phrase);
    if(fprintf(client, "Content-Length: %lu\r\n\r\n%d %s", sizeof(message_body)+4, code, message_body)<0){
        exit(-1);
    }
}

void send_response_file(FILE * client, int code, const char * reason_phrase, int size){
    send_status(client, code, reason_phrase);
    if(fprintf(client, "Content_Length: %d\r\n", size)<0){
        exit(-1);
    }
}
