/*
 * 3-4. In a two's complement number representation, our version of itoa does not
 * handle the largest negative number, that is, the value of n equal to -(2 wordsize-1 ). Explain why
 * not. Modify it to print that value correctly, regardless of the machine on which it runs.
 *
 * wy-ei 2015.1.22
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void itoa1(int n, char *s);
void itoa2(int n, char *s);
void reverse(char *s);
int main() {
    int n = INT_MIN;

    char s[20];
    //version 1
    itoa1(n + 1, s);
    printf("result(version 1):%s\n", s);
    //version 2
    itoa2(n, s);
    printf("result(version 2):%s\n", s);

    return EXIT_SUCCESS;
}
void reverse(char *s) {
    char c;
    int i, j = 0;
    while(s[j] != '\0') {
        j++;
    }
    for(i = 0, j -= 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itoa1(int n, char *s) {
    int sign, i;
    i = 0;
    if((sign = n) < 0) { //buggy! if n=INT_MIN,-n is INT_MIN too.
        n = -n;
    }
    do {
        s[i++] = n % 10 + '0';
    } while((n /= 10) > 0);

    if(sign < 0) {
        s[i++] = '-';
    }
    s[i] = '\0';
    reverse(s);
}

void itoa2(int n, char *s) {
    int sign, i;
    i = 0;
    do {
        s[i++] = abs(n % 10) + '0';
    } while((n /= 10) != 0);
    if(sign < 0) {
        s[i++] = '-';
    }
    s[i] = '\0';
    reverse(s);
}
