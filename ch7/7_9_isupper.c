/*
 * 7-9. Functions like isupper can be implemented to save space or to save time.
 * Explore both possibilities.
 *
 * wy-ei 2015.2.20
 *
*/


#include <stdio.h>

#define isupper1(c) ((c)>='A'&&(c)<='D') //save time


int isupper2(int c) { //save space
    return c >= 'A' && c <= 'D';
}


int main() {
    char c = 'A';
    printf("%d\n", isupper1(c));
    printf("%d\n", isupper2(c));

    return 0;
}
