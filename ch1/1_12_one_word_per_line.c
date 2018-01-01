/*
 * 1-12. Write a program that prints its input one word per line.
 *
 *  wangyu 2015.1.18
*/

#include <stdio.h>

const int in = 0, out = 1;

int main() {
    int c;
    int state = out;
    while((c = getchar()) != EOF) {
        if(c == '\n' || c == '\t' || c == ' ') {
            if(state != out) {
                state = out;
                putchar('\n');
            }
        } else if(state == out) {
            state = in;
            putchar(c);
        } else {
            putchar(c);
        }
    }
    return 0;
}

