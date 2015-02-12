#include "son.h"
#include "message.h"
#include "request.h"
#include <string.h>
#include <stdlib.h>

void traitement_fils(int fd_client){
    const char * mode;
    /*mode lecture et ecriture pour la structure FILE * a partir du descripteur de la socket cliente client*/
    mode="w+";
    /*motd: message d'acueil du serveur*/
    const char * motd;
    motd="Bienvenue sur mon serveur aventurier! Serais tu un ennemi des comanches? si tel est le cas, je te conseille de te deconnecter très vite de ce serveur.. sinon, bienvenue a toi dans notre tribu, tu seras notre invite jusqu'a ce que tu decides de couper la connection qui nous lie. Nous t'offrirons tout ce dont tu as besoin, il te suffira de demander. Prends garde, les comanches sont de vieux indiens rusés et ils adorent faire des farces! ne t'etonne pas si certains de tes fichiers disparaissent ou bien si certains fichiers se creent tout seul sur ton ordinateur, ce ne sera jamais rien de mechant tu peux me faire confiance. Si tu as un probleme quelconque, viens donc voir kaal-dam, le chef de notre tribu, il pourra te depanner avec ses super pouvoirs! sinon, contactes maverick, ce vieux bougre n'est jamais loin et en general il est toujours volontaire pour aider! Evites aussi de parler aux comanches qui sont trop vieux comme serveuris qui t'heberge actuellement, il a tendance a repeter betement tout ce qu'on lui dit, et le pire c'est que ça l'amuse..\n";
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
        send_response(data_stream, 400, "Bad Request", "Bad request\r\n");
    }else{
        if(req.method==HTTP_UNSUPPORTED){
            send_response(data_stream, 405, "Method Not Allowed", "Method not allowed\r\n");
        }else if(strcmp(req.url, "/")==0){
            send_response(data_stream, 200, "OK", motd);
        }else{
            send_response(data_stream, 404, "Not Found", "Page Not Found\r\n");
        }
    }
    /*fils termine*/
    exit(0);
}
