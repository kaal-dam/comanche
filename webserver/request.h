#include <stdio.h>
/*enumeration des methodes supportees*/
enum http_method{
    HTTP_GET,
    HTTP_UNSUPPORTED,
};

/*structure contenant les infos de la premiere ligne de requete http*/
typedef struct{
    enum http_method method;
    int major_version;
    int minor_version;
    char url[512];
}http_request;

char *fgets_or_exit(char *buff, int size, FILE * stream);
void skip_headers(FILE * stream);
int parse_http_request(const char * request_line, http_request *request);
void rewrite_url(char *url);
