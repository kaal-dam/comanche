#include <stdio.h>
enum http_method{
    HTTP_GET,
    HTTP_UNSUPPORTED,
};

typedef struct{
    enum http_method method;
    int major_version;
    int minor_version;
    char * url;
}http_request;

char *fgets_or_exit(char *buff, int size, FILE * stream);
void skip_headers(FILE * stream);
int parse_http_request(const char * request_line, http_request *request);
char *rewrite_url(char *url);
