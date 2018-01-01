/*
 * 1-18. Write a program to remove trailing blanks and tabs from each line of input,
 * and to delete entirely blank lines.
 *
 * wy-ei 2015.1.18
 *
*/

#include <stdio.h>
#include <ctype.h>

#define MAXLINE 1000

int isBlankLine(const char str[]);
void rmTrailingBlank(char str[]);
int my_getline(char str[], int len);

int main() {
    char line[MAXLINE];
    int len;
    while((len = my_getline(line, MAXLINE)) > 0) {
        if(isBlankLine(line))
            continue;
        rmTrailingBlank(line);
        printf("%s", line);
    }
    return 0;
}

int isBlankLine(const char str[]) {
    int i = 0;
    char c;
    while((c = str[i]) != '\0') {
        ++i;
        if(!isblank(c) && c != '\n') {
            return 0;
        }
    }
    return 1;
}

void rmTrailingBlank(char str[]) {
    int len = 0;
    while(*str) { //get length
        ++len;
        ++str;
    }

    while(isblank(str[len - 1])) {
        --len;
    }
    str[len] = '\0';
}

int my_getline(char str[], int len) {
    int c, i;
    for(i = 0; i < len - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        str[i] = c;
    }
    if(c == '\n') {
        str[i] = c;
        i++;
    }
    str[i] = '\0';

    return i;
}

