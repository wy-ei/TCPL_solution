/*
 * 5-13. Write the program tail , which prints the last n lines of its input. By default, n
 * is set to 10, let us say, but it can be changed by an optional argument so that
 * tail -n
 * prints the last n lines. The program should behave rationally no matter how unreasonable the
 * input or the value of n. Write the program so it makes the best use of available storage; lines
 * should be stored as in the sorting program of Section 5.6, not in a two-dimensional array of
 * fixed size.
 *
 * wy-ei 2015.2.9
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1000


int lines = 10;
char *lineptr[MAXLEN];

void getopt(int argc, char *argv[]);
int _getline(char *line, size_t maxlength);
int tail(char **lineptr);

int main(int argc, char *argv[]) {
    getopt(argc, argv);
    tail(lineptr);
    return EXIT_SUCCESS;
}


void getopt(int argc, char *argv[]) {
    if(argc == 1) {
        return;
    } else {
        lines = atoi(argv[1]);
    }
}
int _getline(char *line, size_t maxlength) {
    int i, c;
    for(i = 0; i < maxlength - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
        line[i] = c;
    }
    if(c == '\n') {
        line[i++] = c;
    }
    line[i] = '\0';
    return i;
}
int tail(char *lineptr[]) {

    int len, nlines;
    char *p, line[MAXLEN];
    nlines = 0;

    /*store lines*/
    while((len = _getline(line, MAXLEN)) > 0 && (p = malloc(len)) != NULL) {
        line[len - 1] = '\0';
        strcpy(p, line);
        lineptr[nlines % lines] = p; // use a queue
        nlines++;
    }


    /*print lines*/
    int i;
    if(nlines > lines) { // if input lines is great than set lines
        int begin = nlines % lines; //get start position
        for(i = begin; i < lines; i++) {
            printf("%s\n", lineptr[i]);
        }
        for(i = 0; i < begin; i++) {
            printf("%s\n", lineptr[i]);
        }
    } else {			// if less
        for(i = 0; i < nlines; i++) {
            printf("%s\n", lineptr[i]);
        }
    }
}


