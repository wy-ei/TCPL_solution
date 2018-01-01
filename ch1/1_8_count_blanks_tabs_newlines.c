/*
 * 1-8. Write a program to count blanks, tabs, and newlines.
 *
 * wangyu 2015.1.17
*/

#include <stdio.h>
int main() {
    int nb, nt, nl; //number of blanks,tabs,lines
    nb = nt = nl = 0;
    int c;
    while((c = getchar()) != EOF) {
        if(c == ' ') {
            ++nb;
        } else if(c == '\t') {
            ++nt;
        } else if(c == '\n') {
            ++nl;
        }
    }
    printf("blanks:%d tabs:%d lines:%d\n", nb, nt, nl);

    return 0;
}
