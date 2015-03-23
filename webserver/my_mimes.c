#include "my_mimes.h"
#include <string.h>
#include <stdio.h>

/*recupere la partie a droite du point si celui ci est present dans la chaine passee en parametre*/
char *get_after_point(char *heystack){
    int parties=0;
    char * res;
    const char * chaine=heystack;
    char osef[2048], needle[2048];
    /*si un point est present dans la chaine, on recupere un pointeur vers la premiere occurence de ce caractere*/
    if((res=strchr(heystack, '.'))!=NULL){
        /*remplacement du point par un espace*/
        *res=' ';
        /*la chaine est coupee en deux par rapport à l'espace*/
        if((parties=sscanf(chaine, "%s %s", osef, needle))==2){
            res=needle;
            /*renvoi du truc derriere l'espace*/
            return res;
        }
    }
    /*pas de point dans la chaine*/
    return "";
}

/*regarde l'extension du fichier pointe par url et renvoie le mime type correspondant*/
char *get_mime_type(char * url){
    /*tableau contenant 58 extensions de fichier et le type mime qui leur correspond (mime_correspondance)*/
    mime_correspondance mime_correspondances[58]={{"application/java-archive", "jar"}, {"application/java-vm", "class"}, {"application/javascript", "js"}, {"application/json", "json"}, {"application/octet-stream", "bin"}, {"application/pdf", "pdf"}, {"application/rar", "rar"}, {"application/xml", "xml"}, {"application/xml", "xsl"}, {"application/xml", "xsd"}, {"application/zip", "zip"}, {"application/vnd.ms-excel", "xls"}, {"application/vnd.ms-excel", "xlb"}, {"application/vnd.ms-excel", "xlt"}, {"application/vnd.ms-powerpoint", "ppt"}, {"application/vnd.ms-powerpoint", "pps"}, {"application/x-7z-compressed", "7z"}, {"application/x-bittorrent", "torrent"}, {"application/x-debian-package", "deb"}, {"application/x-debian-package", "udeb"}, {"application/x-dvi", "dvi"}, {"application/x-gtar-compressed", "tgz"}, {"application/x-gtar-compressed", "taz"}, {"application/x-iso9660-image", "iso"}, {"application/x-md5", "md5"}, {"application/x-msdos-program", "exe"}, {"application/x-msdos-program", "bat"}, {"application/x-msdos-program", "dll"}, {"application/x-redhat-package-manager", "rpm"}, {"application/x-ruby", "rb"}, {"application/x-sh", "sh"}, {"application/x-sql", "sql"}, {"application/x-tar", "tar"}, {"audio/flac", "flac"}, {"audio/mpeg", "mp3"}, {"audio/x-ms-wma", "wma"}, {"audio/x-wav", "wav"}, {"image/gif", "gif"}, {"image/jpeg", "jpeg"}, {"image/jpeg", "jpg"}, {"image/jpeg", "jpe"}, {"image/png", "png"}, {"text/css", "css"}, {"text/csv", "csv"}, {"text/x-chdr", "h"}, {"text/x-csrc", "c"}, {"text/x-java", "java"}, {"text/x-sh", "sh"}, {"text/x-perl", "pl"}, {"text/x-perl", "pm"}, {"video/mpeg", "mpeg"}, {"video/mp4", "mp4"}, {"video/x-msvideo", "avi"}, {"video/x-matroska", "mkv"}, {"application/vnd.oasis.opendocument.text", "odt"}, {"application/vnd.oasis.opendocument.presentation", "odp"}, {"text/html", "html"}, {"text/plain", "txt"}};
    int i;
    char *extension_prec=url, *extension;
    /*tant qu'il y a des points dans la chaine, on recupere la partie a droite du premier point croise*/
    while(strcmp((extension=get_after_point(extension_prec)), "")!=0){
        extension_prec=extension;
    }
    /*taille du tableau des correspondances ext/mime_type*/
    int length=sizeof(mime_correspondances)/sizeof(mime_correspondance);
    /*pour tous les elements du tableau*/
    for(i=0; i<length; i++){
        /*si l'extension du fichier demande dans url correspond a l'extension contenue a la case i du tableau*/
        if(strcmp(extension_prec, mime_correspondances[i].extension)==0){
            /*renvoyer le type mime correspondant contenu a la case i du tableau*/
            return mime_correspondances[i].mime_type;
        }
    }
    /*si l'extension du fichier demande ne correspond a aucune traitee par le serveur*/
    return "text/plain";
}
