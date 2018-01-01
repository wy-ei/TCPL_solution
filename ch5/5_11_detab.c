/*
 * 1-20. Write a program detab that replaces tabs in the input with the proper number
 * of blanks to space to the next tab stop. Assume a fixed set of tab stops, say every n columns.
 * Should n be a variable or a symbolic parameter?
 *
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define  N 4

int stops;

char* detab(char *str);

int main(int argc, char *argv[]) {
    if(argc == 1) {
        stops = N;
    } else {
        stops = atoi(argv[1]);
    }
    char *line = malloc(1024);
    int len;
    char *newline;
    while(getline(&line, &len, stdin) != -1) {
        newline = detab(line);
        printf("%s", newline);
        free(newline);
    }
    free(line);
    return 0;
}
char* detab(char *str) {
    int len = 0, num = 0;
    int i = 0;
    char c;
    while((c = str[i]) != '\0') {
        if(c == '\t') { // get the number of tab
            num++;
        }
        len++;			// get length of string
        i++;
    }
    char *newline;
    newline = malloc(sizeof(char) * (len + (stops - 1) * num + 1)); //use four blank replace one tab
    if(newline == NULL) {
        fprintf(stderr, "can't malloc space\n");
        exit(0);
    }
    i = 0;
    int j = 0;		//index of newline
    while((c = str[i]) != '\0') {
        if(c == '\t') {
            int k;
            for(k = 0; k < stops; k++) {
                newline[j] = ' ';
                ++j;
            }
        } else {
            newline[j] = c;
            ++j;
        }
        ++i;
    }
    newline[j] = '\0';
    return newline;
}

