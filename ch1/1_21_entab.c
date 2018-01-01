/*
 * 1-21. Write a program entab that replaces strings of blanks by the minimum
 * number of tabs and blanks to achieve the same spacing. Use the same tab stops as for detab .
 * When either a tab or a single blank would suffice to reach a tab stop, which should be given
 * preference?
 *
 * wy-ei 2015.1.21
 *
*/

#include <stdio.h>
#define N 4

int main() {
    int c;
    int nb = 0; //number of blank
    int nt = 0; //number of tab
    while((c = getchar()) != EOF) {
        if(c == ' ') {
            nb++;
            continue;
        }
        if(c == '\t') {
            nb += N;
            continue;
        }
        if(nb == 0) {
            putchar(c);
        } else {
            nt = nb / N;
            nb = nb % N;
            while(nt != 0) {
                putchar('\t');
                nt--;
            }
            while(nb != 0) {
                putchar(' ');
                nb--;
            }
            putchar(c);
        }
    }
    return 0;
}

