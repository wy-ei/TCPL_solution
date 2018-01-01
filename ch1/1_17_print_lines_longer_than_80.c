/*
 * 1-17. Write a program to print all input lines that are longer than 80 characters.
 *
 * wy-ei 2015.1.18
 *
*/

#include <stdio.h>

#define MAXLINE 1000

int my_getline(char str[], int len) {
    int i, c;
    for(i = 0; i < len - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        str[i] = c;
    }
    if(c == '\n') {
        str[i] = c;
        ++i;
    }
    str[i] = '\0';

    return i;
}

int main() {
    char line[MAXLINE];
    int  len;
    while((len = my_getline(line, MAXLINE)) > 0) {
        if(len > 80) {
            printf("%s", line);
        }
    }
    return 0;
}



