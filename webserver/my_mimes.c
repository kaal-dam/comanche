#include "my_mimes.h"
#include <string.h>
#include <stdio.h>

/*regarde l'extension du fichier pointe par le lien root_directory concatene avec url et renvoie le mime type correspondant*/
char *get_mime_type(char * url){
    char * extension;
    if((extension=strstr(url, ".html"))!=NULL){
        return "text/html";
    }
    return "plain/text";
}
