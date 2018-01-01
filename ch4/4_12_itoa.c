/*
 * 4-12. Adapt the ideas of printd to write a recursive version of itoa ; that is, convert
 * an integer into a string by calling a recursive routine.
 *
 * wy-ei 2015.1.24
*/

#include <stdio.h>
#include <stdlib.h>

void itoa(int, char *);

int main() {
    int n = 211314;
    char v[20];
    itoa(n, v);
    printf("%s\n", v);
    return EXIT_SUCCESS;
}

void itoa(int n, char *s) {
    static int i = 0;
    if(n / 10) {
        itoa(n / 10, s);
    }
    s[i++] = n % 10 + '0';
    s[i] = '\0';
}



