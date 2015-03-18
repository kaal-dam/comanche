#include "son.h"
#include "message.h"
#include "request.h"
#include <string.h>
#include <stdlib.h>
#include "my_file.h"
#include "my_mimes.h"
#include "my_stats.h"

void traitement_fils(int fd_client, const char *root_dir){
    /*descripteur du fichier*/
    int fdFile;
    /*taille du fichier*/
    int size;
    const char * mode;
    /*mode lecture et ecriture pour la structure FILE * a partir du descripteur de la socket cliente client*/
    mode="w+";
    /*premiere ligne de la requete http envoyee par le client*/
    char req_http[3124];
    FILE * data_stream=NULL;
    /*obtenir une structure FILE * a partir du descripteur correspondant a la socket cliente client et dans le mode specifie*/
    data_stream=fdopen(fd_client, mode);
    if(data_stream==NULL){
        perror("fdopen");
        exit(-1);
    }
    /*où stocker infos de la premiere ligne requete http*/
    http_request req;
    //lecture 1ere ligne requete http
    fgets_or_exit(req_http, 3124, data_stream);
    //passage des autres lignes de la requete
    skip_headers(data_stream);
    //stockage des infos + verif de la requete et affichage des messages en consequence
    if(parse_http_request(req_http, &req)==0){
        /*requete invalide*/
        /*methode non supportee*/
        if(req.method==HTTP_UNSUPPORTED){
            send_response(data_stream, 405, "Method Not Allowed", "Method Not Allowed\r\n");
        /*version non supportee*/
        }else if(req.major_version!=1 || (req.minor_version!=0 && req.minor_version!=1)){
            send_response(data_stream, 505, "HTTP Version Not Supported", "HTTP Version Not Supported\r\n");
        /*requete incorrecte*/
        }else{
            send_response(data_stream, 400, "Bad Request", "Bad Request\r\n");
            get_stats()->ko_400+=1;
        }
    }else{
        /*requete valide*/
        char *forbidden_substring;
        /*verification qu'on ne sort pas du repertoire traite par le serveur*/
        if((forbidden_substring=strstr(req.url, "/../"))!=NULL){
            /*la ressource demandee est en dehors du repertoire, interdit*/
            send_response(data_stream, 403, "Forbidden", "Changing directory is forbidden to this server\r\n");
            get_stats()->ko_403+=1;
        }else{
            /*ne sort pas du repertoire traite par le serv.*/
            /*si l'url demande est stats*/
            if(strcmp(req.url, "/stats")==0){
                send_stats(data_stream);
                get_stats()->ok_200+=1;
            /*verif que le chemin vers la ressource demandee est correcte (mene a un fichier existant, sur lequel on a les droits etc..) et obtention descripteur vers ce fichier ouvert*/
            }else{ 
                if((fdFile=check_and_open(req.url, root_dir))!=-1){
                    char * mime_type;
                    /*obtention taille du contenu du fichier*/
                    size=get_file_size(fdFile);
                    /*obtention mime type*/
                    mime_type=get_mime_type(req.url);
                    /*reponse OK sans contenu*/
                    send_response_file(data_stream, 200, "OK", size, mime_type);
                    /*envoie contenu au client*/
                    if(copy(fdFile, fd_client)<size){
                        exit(-1);
                    }
                    get_stats()->ok_200+=1;
                /*chemin demande ne mene pas a un fichier correct (inexistant)*/
                }else{
                    send_response(data_stream, 404, "Not Found", "Page Not Found\r\n");
                    get_stats()->ko_400+=1;
                }
            }
        }
    }
    /*fils termine*/
    get_stats()->served_requests+=1;
    exit(0);
}
