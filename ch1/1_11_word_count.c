/*
 * 1-11. How would you test the word count program? What kinds of input are most
 * likely to uncover bugs if there are any?
 *
 * wangyu 2015.1.18
*/

#include <stdio.h>

const int in = 0, out = 1;

int main() {
    int c;
    int nl, nw, nc; //number of lines ,words and charaters
    nl = nw = nc = 0;
    int state = out;
    while((c = getchar()) != EOF) {
        nc++;
        if(c == '\n') {
            nl++;
        }
        if(c == '\n' || c == '\t' || c == ' ') {
            state = out;
        } else if(state == out) {
            state = in;
            nw++;
        }
    }
    printf("%d %d %d\n", nl, nw, nc);
    return 0;
}
