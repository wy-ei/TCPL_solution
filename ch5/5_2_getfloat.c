/*
 * 5-2. Write getfloat , the floating-point analog of getint . What type does
 * getfloat return as its function value?
 *
 * wy-ei 2015.1.28
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define BUFMAXSIZE 100

char buf[BUFMAXSIZE];
int bufp = 0;

int getch();
void ungetch(char);
int getfloat(float *);

int main() {
    float f;

    while(getfloat(&f) != EOF) {
        printf("%f\n", f);
    }

    return EXIT_SUCCESS;
}

int getch() {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(char c) {
    if(bufp < BUFMAXSIZE - 1) {
        buf[bufp++] = c;
    } else {
        printf("error:buf is full.\n");
    }
}

int getfloat(float *f) {
    int sign, c;
    float val;
    while(isspace(c = getch())) //skip space
        ;

    if(!isdigit(c) && c != '+' && c != '-' && c != EOF) {
        ungetch(c);			// not a number
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    if(c == '+' || c == '-') {
        c = getch();
    }

    for(val = 0; isdigit(c); c = getch()) {
        val = val * 10 + c - '0';
    }

    int	power = 0;
    if(c == '.') {
        for(c = getch(); isdigit(c); c = getch()) {
            power++;
            val = val * 10 + c - '0';
        }
        if(c != EOF) {
            ungetch(c);
        }
    } else {
        ungetch(c);
    }

    val = sign * val / pow(10, power);
    c = getch();
    int exp = 0;
    double index = 0;
    if(c == 'e' || c == 'E') {

        c = getch();
        index = (c == '-') ? 0.1 : 10;
        if(c != '+' && c != '-') {
            ungetch(c);
        }

        for(c = getch(); isdigit(c); c = getch()) {
            exp = exp * 10 + c - '0';
        }
        val *= pow(index, exp);
    } else {
        ungetch(c);
    }


    *f = val;

    if(c != EOF) {
        ungetch(c);
    }

    return c;

}

