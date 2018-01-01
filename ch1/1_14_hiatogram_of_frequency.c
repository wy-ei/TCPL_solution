/*
 * 1-14. Write a program to print a histogram of the frequencies of different characters
 * in its input.
 *
 * wy-ei 2015.1.18
*/

#include <stdio.h>
#include <ctype.h>

int main() {
    char charArray[128];
    int i, n, num;
    int c;
    for(i = 0; i < 128; i++) {
        charArray[i] = 0;
    }
    while((c = getchar()) != EOF) {
        charArray[c]++;
    }
    for(i = 0; i < 128; i++) {
        if(isprint(i)) {    //is this character printable
            printf("%c:", i);
            num = charArray[i];
            for(n = 0; n < num; n++) {
                putchar('=');
            }
            putchar('\n');
        }
    }
    return 0;
}
