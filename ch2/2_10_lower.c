/*
 * 2-10. Rewrite the function lower , which converts upper case letters to lower case,
 * with a conditional expression instead of if-else .
 *
 * wy-ei 2015.1.22
*/

#include <stdio.h>

char lower(char c) {
    return (c >= 'A' && c <= 'Z') ? (c - 'A' + 'a') : c;
}

int main() {
    int n = 'A';
    while(n <= 'Z') {
        printf("lower(%c)=%c\n", n, lower(n));
        n++;
    }
    return 0;
}
