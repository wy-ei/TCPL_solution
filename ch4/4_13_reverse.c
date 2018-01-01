/*
 * 4-13. Write a recursive version of the function reverse(s) , which reverses the
 * string s in place.
 *
 * wy-ei 2015.1.22
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char *s);

int main() {
    char *s = NULL;
    int len;
    getline(&s, &len, stdin);

    reverse(s);

    printf("%s\n", s);

    return EXIT_SUCCESS;
}

void reverse(char *s) {
    void reverser(char *s, int i, int len);
    reverser(s, 0, strlen(s));
}

void reverser(char *s, int i, int len) {
    int c;
    int j;

    j = len - i - 1;

    if(i < j) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
        reverser(s, ++i, len);
    }
}
