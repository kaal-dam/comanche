# comanche
Bienvenue dans le README de notre serveur comanche!
Comanche est un serveur web minimaliste. Néammoins, il gère les types mime et ne sert donc pas que des pages web.

Pour utiliser le serveur, rien de plus simple. Il suffit de se placer dans le dossier comanche/webserver et de faire un make pour compiler le programme.

Une fois compilé, il suffit de taper ./comanche pour lancer un serveur en local sur votre machine, par defaut sur le port 8080.

Vous pourrez ensuite demander au serveur, par exemple avec un navigateur web ou netcat, une ressource voulue.

Les ressources servies par comanche se trouvent par defaut dans le dossier comanche/resources. Le serveur est configuré pour ne pas servir les requetes si la ressource demandée n'est pas dans ce dossier ou un de ses sous dossiers (si vous en créez). Attention, si la requete faite au serveur comporte un /../ dans l'url, le serveur refusera de servir la ressource même si on retourne au document_root!

la page servie par défaut est index.html

Si vous faites une requete sur la ressource /stats, le serveur vous renverra ses statistiques sur les différentes requêtes traitées depuis qu'il a été démarré

Les methodes supportées actuellement par le serveur: GET

Versions supportées: HTTP/1.1 et HTTP/1.0

Si vous voulez régler le serveur:

PORT: éditer le fichier comanche/webserver/main.c et changer le paramètre de la fonction creer_serveur par le port que vous voulez (celui ci doit être libre).

DOSSIER: éditer le fichier comanche/webserver/main.c et changer la valeur de la variable document_root par la valeur voulue (le dossier doit éxister!)

PAGE PAR DEFAUT: éditer le fichier comanche/webserver/request.c et dans la méthode rewrite_url changer index.html en la ressource voulue (le fichier doit éxister)

