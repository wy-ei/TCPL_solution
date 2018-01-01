/*
 * 5-1. As written, getint treats a + or - not followed by a digit as a valid
 * representation of zero. Fix it to push such a character back on the input.
 *
 * wy-ei 2015.1.27
*/


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int getint(int *pn);

int main() {
    int a;

    while(getint(&a) != EOF) {
        printf("%d\n", a);
    }

    return EXIT_SUCCESS;
}

#define MAXBUFSIZE  100

int getch();
void ungetch(int);

char buf[MAXBUFSIZE];
int bufp = 0;

int getch() {
    return bufp > 0 ? buf[--bufp] : getchar();
}

void ungetch(int ch) {
    if(bufp < MAXBUFSIZE - 1) {
        buf[bufp] = ch;
        bufp++;
    } else {
        printf("error:buf is full.\n");
    }
}

int getint(int *pn) {
    int c, sign;
    while(isspace(c = getch()))
        ;
    if(!isdigit(c) && c != '+' && c != '-' && c != EOF) {
        ungetch(c);   // not a number
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if(c == '+' || c == '-') {
        c = getch();
        if(!isdigit(c)) {
            ungetch(c);
            ungetch(sign == 1 ? '+' : '-');
            return 0;
        }
    }
    for(*pn = 0; isdigit(c); c = getch()) {
        *pn = *pn * 10 + c - '0';
    }
    *pn *= sign;
    if(c != EOF) {
        ungetch(c);
    }
    return c;
}
