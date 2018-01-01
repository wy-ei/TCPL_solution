/*
 * 5-5. Write versions of the library functions strncpy , strncat , and strncmp , which
 * operate on at most the first n characters of their argument strings. For example,
 * strncpy(s,t,n) copies at most n characters of t to s .
 *
 * wy-ei 2015.1.30
*/

#include <stdio.h>
#include <stdlib.h>

char *strncpy(char *dest, const char *src, size_t n);
char *strncat(char *dest, const char *src, size_t n);
int   strncmp(char *s, char *t, size_t n);
size_t strlen_(char *s);

int main() {
    char dest[30];
    char *a = "The c programming ";
    char *b = "language";
    char *c = "age.";
    char *d = "lbng...";

    strncpy(dest, a, strlen_(a));
    printf("strncpy : %s\n", dest);

    strncat(dest, b, 5);
    printf("strncat : %s\n", dest);

    strncat(dest, c, 4);
    printf("strncat : %s\n", dest);

    printf("strncmp : %d\n", strncmp(b, d, 4));

    return EXIT_SUCCESS;
}


char *strncpy(char *dest, const char *src, size_t n) {
    int i;
    for(i = 0; i < n && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return dest;
}

char *strncat(char *dest, const char *src, size_t n) {
    size_t len = strlen_(dest);
    int i;
    for(i = 0; i < n && src[i] != '\0'; i++) {
        dest[len + i] = src[i];
    }
    dest[len + i] = '\0';
    return dest;
}

int   strncmp(char *s, char *t, size_t n) {
    int i;
    for(i = 0; s[i] == t[i] && i < n; i++)
        ;
    if(i == n) {
        return 0;
    } else {
        return s[i] - t[i];
    }
}

size_t strlen_(char *s) {
    char *t = s;
    while(*s) {
        s++;
    }
    return s - t;
}
