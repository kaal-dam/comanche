#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int check_and_open(const char *url, const char *document_root);
int get_file_size(int fd);
int copy(int fd_in, int fd_out);
