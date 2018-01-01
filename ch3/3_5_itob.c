/*
 * 3-5. Write the function itob(n,s,b) that converts the integer n into a base b
 * character representation in the string s . In particular, itob(n,s,16) formats s as a
 * hexadecimal integer in s .
 *
 * wy-ei 2015.1.22
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

void itob(int n, char *s, int b);
void reverse(char *s);
int main() {
    int n1 = INT_MAX;
    int n2 = INT_MIN;

    char s[20];

    itob(n1, s, 16);
    printf("%s\n", s);

    itob(n2, s, 16);
    printf("%s\n", s);

    return EXIT_SUCCESS;
}

void itob(int n, char *s, int b) {
    int sign, i = 0;
    sign = n;

    while((n /= b) != 0) {
        if(b <= 10) {
            s[i++] = abs(n % b) + '0';
        } else {
            s[i++] = abs(n % b) > 10 ? (abs(n % b) + 'a' - 10) : (abs(n % b) + '0');
        }
    }
    if(sign < 0) {
        s[i++] = '-';
    }
    s[i] = '\0';
    reverse(s);
}
void reverse(char *s) {
    int i, j, c;
    for(i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
