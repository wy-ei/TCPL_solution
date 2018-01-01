#include <stdio.h>
#include <string.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "dirent.h"
#include <stdlib.h>
void fsize(char *);

int main(int argc, char *argv[]) {
    if(argc == 1) {
        fsize(".");
    } else {
        while(--argc) {
            fsize(*++argv);
        }
    }
    return 0;
}

void dirwalk(char *, void (*fcn)(char *));

/* fsize: print the name of file "name" */
void fsize(char *name) {
    struct stat stbuf;
    if (stat(name, &stbuf) == -1) {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }
    if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
        dirwalk(name, fsize);
    printf("%8ld %s\n", stbuf.st_size, name);
}


#define MAX_PATH 1024
/* dirwalk: apply fcn to all files in dir */
void dirwalk(char *dir, void (*fcn)(char *)) {
    char name[MAX_PATH];
    Dirent *dp;
    DIR *dfd;
    if ((dfd = opendir(dir)) == NULL) {
        fprintf(stderr, "dirwalk: can't open %s\n", dir);
        return;
    }
    while ((dp = readdir(dfd)) != NULL) {
        if (strcmp(dp->name, ".") == 0
                || strcmp(dp->name, ".."))
            continue;
        /* skip self and parent */
        if (strlen(dir) + strlen(dp->name) + 2 > sizeof(name))
            fprintf(stderr, "dirwalk: name %s %s too long\n",
                    dir, dp->name);
        else {
            sprintf(name, "%s/%s", dir, dp->name);
            (*fcn)(name);
        }
    }
    closedir(dfd);
}
