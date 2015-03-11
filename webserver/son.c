#include "son.h"
#include "message.h"
#include "request.h"
#include <string.h>
#include <stdlib.h>
#include "my_file.h"

void traitement_fils(int fd_client, const char *root_dir){
    /*descripteur du fichier*/
    int fdFile;
    /*taille du fichier*/
    int size;
    const char * mode;
    /*mode lecture et ecriture pour la structure FILE * a partir du descripteur de la socket cliente client*/
    mode="w+";
    /*motd: message d'acueil du serveur*/
    /*const char * motd;
    motd="Bienvenue sur mon serveur aventurier! Serais tu un ennemi des comanches? si tel est le cas, je te conseille de te deconnecter tres vite de ce serveur.. sinon, bienvenue a toi dans notre tribue, tu seras notre invite jusqu'a ce que tu decides de couper la connection qui nous lie. Nous t'offrirons tout ce dont tu as besoin, il te suffira de demander. Prends garde, les comanches sont de vieux indiens ruses et ils adorent faire des farces! Aussi, ne t'etonne pas si certains de tes fichiers disparaissent ou bien si certains fichiers se creent tout seul sur ton ordinateur, ce ne sera jamais rien de mechant tu peux me faire confiance. Si tu as un probleme quelconque, viens donc voir kaal-dam, le chef de notre tribu, il pourra te depanner avec ses super pouvoirs! sinon, contactes maverick, ce vieux bougre n'est jamais loin et en general il est toujours volontaire pour aider! Evites aussi de parler aux comanches qui sont trop vieux comme serveuris qui t'heberge actuellement, il a tendance a repeter betement tout ce qu'on lui dit, et le pire c'est que ca l'amuse..\n";*/
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
        if(req.method==HTTP_UNSUPPORTED){
            send_response(data_stream, 405, "Method Not Allowed", "Method Not Allowed\r\n");
        }else if(req.major_version!=1 || (req.minor_version!=0 && req.minor_version!=1)){
            send_response(data_stream, 505, "HTTP Version Not Supported", "HTTP Version Not Supported\r\n");
        }else{
            send_response(data_stream, 400, "Bad Request", "Bad Request\r\n");
        }
    }else{
        if((fdFile=check_and_open(req.url,root_dir))!=-1){
            size=get_file_size(fdFile);
            send_response_file(data_stream, 200, "OK", size);
            if(copy(fdFile, fd_client)<size){
                exit(-1);
            }
        }else{
            send_response(data_stream, 404, "Not Found", "Page Not Found\r\n");
        }
    }
    /*fils termine*/
    exit(0);
}
