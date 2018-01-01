/*
 * 5-6. Rewrite appropriate programs from earlier chapters and exercises with pointers
 * instead of array indexing. Good possibilities include getline (Chapters 1 and 4), atoi , itoa ,
 * and their variants (Chapters 2, 3, and 4), reverse (Chapter 3), and strindex and getop (Chapter 4).
 *
 * wy-ei 2015.2.6
*/


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int _getline(char *, int);
int _atoi(char *);
void _itoa(int, char *);
void _reverse(char *);

int main() {
    char s[20];
    _getline(s, 20);
    printf("%s\n", s);
    char ss[] = "wangyuiswangyu";
    _reverse(ss);
    printf("%s\n", ss);
    char *numstr = "54321";
    int n = _atoi(numstr);
    printf("%d\n", n);
    _itoa(n, ss);
    printf("%s\n", ss);
    return EXIT_SUCCESS;
}


int _getline(char *s, int n) {
    int c;
    int i = 0;
    while((c = getchar()) != EOF && i < n - 1 && c != '\n') {
        *s = c;
        s++;
        i++;
    }
    if(c == '\n') {
        *s = c;
        s++;
    }
    *s = '\0';
    return i;
}

int _atoi(char *s) {
    while(isspace(*s)) {
        s++;
    }
    int result = 0;
    while(*s != '\0') {
        result = result * 10 + *s - '0';
        s++;
    }
    return result;
}
void _itoa(int n, char *s) {
    char *str = s;
    while(n) {
        *s = n % 10 + '0';
        s++;
        n = n / 10;
    }
    *s = '\0';

    _reverse(str);
}

void _reverse(char *s) {
    int len = 0;
    char *str = s;
    while(*str != '\0') {
        len++;
        str++;
    }
    int i, j;
    char tmp;
    for(i = 0, j = len - 1; i < j; i++, j--) {
        tmp = *(s + i);
        *(s + i) = *(s + j);
        *(s + j) = tmp;
    }
}
