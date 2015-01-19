#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "socket.h"

int main(int argc, char ** argv){
    int serveur = cree_serveur(8000);
    if(serveur == -1){
        printf("erreur de creation serveur");
        fflush(stdout);
        return -1;
    }
    /*
     *finir la partie socket client
     */
    /*accepter les connexions indefiniment*/
    while(1==1){
        int fd;
        fd=accept(serveur, NULL, NULL);
        if(fd==-1){
            perror("connection to server fail");
            return -1;
        }else{
            /*Connexion d'un client, message de bienvenue*/
            printf("Bienvenue sur mon serveur aventurier! Serais tu un ennemi des comanches? si tel est le cas, je te conseille de te deconnecter très vite de ce serveur.. sinon, bienvenue a toi dans notre tribu, tu seras notre invite jusqu'a ce que tu decides de couper la connection qui nous lie. Nous t'offrirons tout ce dont tu as besoin, il te suffira de demander. Prends garde, les comanches sont de vieux indiens rusés et ils adorent faire des farces! ne t'etonne pas si certains de tes fichiers disparaissent ou bien si certains fichiers se creent tout seul sur ton ordinateur, ce ne sera jamais rien de mechant tu peux me faire confiance. Si tu as un probleme quelconque, viens donc voir kaal-dam, le chef de notre tribu, il pourra te depanner avec ses super pouvoirs! sinon, contactes maverick, ce vieux bougre n'est jamais loin et en general il est toujours volontaire pour aider! Evites aussi de parler aux comanches qui sont trop vieux comme serveuris qui t'heberge actuellement, il a tendance a repeter betement tout ce qu'on lui dit, et le pire c'est que ça l'amuse..");
            /*tant que le client est connecte, on repete ce qu'il nous envoie*/
            while(ECONNABORTED){
                
            }
        }
    }
    return 0;
}
