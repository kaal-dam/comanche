#include "my_mimes.h"
#include <string.h>
#include <stdio.h>

/*regarde l'extension du fichier pointe par url et renvoie le mime type correspondant*/
char *get_mime_type(char * url){
    char * extension;
    if((extension=strstr(url, ".html"))!=NULL){
        return "text/html";
    }else if((extension=strstr(url, ".jar"))!=NULL){
        return "application/java-archive";    
    }else if((extension=strstr(url, ".class"))!=NULL){
        return "application/java-vm";
    }else if((extension=strstr(url, ".js"))!=NULL){
        return "application/javascript";
    }else if((extension=strstr(url, ".json"))!=NULL){
        return "application/json";
    }else if((extension=strstr(url, ".bin"))!=NULL){
        return "application/octet-stream";
    }else if((extension=strstr(url, ".pdf"))!=NULL){
        return "application/pdf";
    }else if((extension=strstr(url, ".rar"))!=NULL){
        return "application/rar";
    }else if((extension=strstr(url, ".xml"))!=NULL || (extension=strstr(url, ".xsl"))!=NULL || (extension=strstr(url, ".xsd"))!=NULL){
        return "application/xml";
    }else if((extension=strstr(url, ".zip"))!=NULL){
        return "application/zip";
    }else if((extension=strstr(url, ".xls"))!=NULL || (extension=strstr(url, ".xlb"))!=NULL || (extension=strstr(url, ".xlt"))!=NULL){
        return "application/vdn.ms-excel";
    }else if((extension=strstr(url, ".ppt"))!=NULL || (extension=strstr(url, ".pps"))!=NULL){
        return "application/vdn.ms-powerpoint";
    }else if((extension=strstr(url, ".7z"))!=NULL){
        return "application/x-7z-compressed";
    }else if((extension=strstr(url, ".torrent"))!=NULL){
        return "application/x-bittorrent";
    }else if((extension=strstr(url, ".deb"))!=NULL || (extension=strstr(url, ".udeb"))!=NULL){
        return "application/x-debian-package";
    }else if((extension=strstr(url, ".dvi"))!=NULL){
        return "application/x-dvi";
    }else if((extension=strstr(url, ".tgz"))!=NULL || (extension=strstr(url, ".taz"))!=NULL){
        return "application/x-gtar-compressed";
    }else if((extension=strstr(url, ".iso"))!=NULL){
        return "application/x-iso9660-image";
    }else if((extension=strstr(url, ".md5"))!=NULL){
        return "application/x-md5";
    }else if((extension=strstr(url, ".exe"))!=NULL || (extension=strstr(url, ".bat"))!=NULL || (extension=strstr(url, ".dll"))!=NULL){
        return "application/x-msdos-program";
    }else if((extension=strstr(url, ".rpm"))!=NULL){
        return "application/x-redhat-package-manager";
    }else if((extension=strstr(url, ".rb"))!=NULL){
        return "application/x-ruby";
    }else if((extension=strstr(url, ".sh"))!=NULL){
        return "application/x-sh";
    }else if((extension=strstr(url, ".sql"))!=NULL){
        return "application/x-sql";
    }else if((extension=strstr(url, ".tar"))!=NULL){
        return "application/x-tar";
    }else if((extension=strstr(url, ".flac"))!=NULL){
        return "audio/flac";
    }else if((extension=strstr(url, ".mp3"))!=NULL){
        return "audio/mpeg";
    }else if((extension=strstr(url, ".wma"))!=NULL){
        return "audio/x-ms-wma";
    }else if((extension=strstr(url, ".wav"))!=NULL){
        return "audio/x-wav";
    }else if((extension=strstr(url, ".gif"))!=NULL){
        return "image/gif";
    }else if((extension=strstr(url, ".jpeg"))!=NULL || (extension=strstr(url, ".jpg"))!=NULL || (extension=strstr(url, ".jpe"))!=NULL){
        return "image/jpeg";
    }else if((extension=strstr(url, ".png"))!=NULL){
        return "image/png";
    }else if((extension=strstr(url, ".css"))!=NULL){
        return "text/css";
    }else if((extension=strstr(url, ".csv"))!=NULL){
        return "text/csv";
    }else if((extension=strstr(url, ".h"))!=NULL){
        return "text/x-chdr";
    }else if((extension=strstr(url, ".c"))!=NULL){
        return "text/x-csrc";
    }else if((extension=strstr(url, ".java"))!=NULL){
        return "text/x-java";
    }else if((extension=strstr(url, ".sh"))!=NULL){
        return "text/x-sh";
    }else if((extension=strstr(url, ".pl"))!=NULL || (extension=strstr(url, ".pm"))!=NULL){
        return "txt/x-perl";
    }else if((extension=strstr(url, ".mpeg"))!=NULL){
        return "video/mpeg";
    }else if((extension=strstr(url, ".mp4"))!=NULL){
        return "video/mp4";
    }else if((extension=strstr(url, ".avi"))!=NULL){
        return "video/x-msvideo";
    }else if((extension=strstr(url, ".mkv"))!=NULL){
        return "video/x-matroska";
    }else if((extension=strstr(url, ".odt"))!=NULL){
        return "application/vnd.oasis.opendocument.text";
    }else if((extension=strstr(url, ".odp"))!=NULL){
        return "application/vnd.oasis.opendocument.presentation";
    }
    return "text/plain";
}
