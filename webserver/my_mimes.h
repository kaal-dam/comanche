typedef struct{
    char * mime_type;
    char * extension;
}mime_correspondance;

char *get_mime_type(char * url);
char *get_after_point(char *heystack);
