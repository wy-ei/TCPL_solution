/*
 * 7-7. Modify the pattern finding program of Chapter 5 to take its input from a set of
 * named files or, if no files are named as arguments, from the standard input. Should the file
 * name be printed when a matching line is found?
 *
 * wy-ei 2015.2.16
 */

#include <stdio.h>
#include <string.h>

#define MAXLEN 1000
int main(int argc, char *argv[]) {
    char *prog = argv[0];
    if(argc < 2) {
        fprintf(stderr, "Usage:%s line [file1 file2 ...]\n", prog);
        return 1;
    }
    char *dst = argv[1];
    char line[MAXLEN];
    unsigned int linenum = 0;
    if(argc == 2) { //read from stdin
        while(fgets(line, MAXLEN, stdin) != NULL) {
            linenum++;
            if(strstr(line, dst) != NULL) {
                printf("find it! at line %d in stdin\n%s", linenum, line);
            }
        }
    } else {
        int i;
        FILE *fp;
        for(i = 2; i < argc; i++) {
            if((fp = fopen(argv[i], "r")) == NULL) {
                fprintf(stderr, "error:can't open file %s\n", argv[i]);
                return 0;
            }
            while(fgets(line, MAXLEN, fp) != NULL) {
                linenum++;
                if(strstr(line, dst) != NULL) {
                    printf("find it! at line %d for %s\n %s", linenum, argv[i], line);
                }
            }
            fclose(fp);
        }

    }
    return 0;
}
