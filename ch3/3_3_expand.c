/*
 * 3-3. Write a function expand(s1,s2) that expands shorthand notations like a-z in
 * the string s1 into the equivalent complete list abc...xyz in s2 . Allow for letters of either
 * case and digits, and be prepared to handle cases like a-b-c and a-z0-9 and -a-z . Arrange
 * that a leading or trailing - is taken literally.
 *
 * wy-ei 2015.1.22
 */


#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

void expand(char *s1, char *s2);

int main() {
    char *a1 = "a-zA-";
    char *a2 = "-zA-G";
    char *a3 = "0-3-9";
    char *a4 = "0-9a-z";

    char s[100] = {0};
    expand(a1, s);
    printf("%s:%s\n", a1, s);

    expand(a2, s);
    printf("%s:%s\n", a2, s);

    expand(a3, s);
    printf("%s:%s\n", a3, s);

    expand(a4, s);
    printf("%s:%s\n", a4, s);

    return 0;
}

void expand(char *s1, char *s2) {
    int i, j, k;
    i = j = 0;
    int min = 0, max = 0;

    for(; s1[i] != '\0'; i++) {
        if(s1[i] == '-') {
            if(i != 0) {
                min = s1[i - 1] + 1;
            } else {     //if first character is '-'
                max = s1[i + 1];
                if(isdigit(max)) {
                    min = '0';
                } else if(islower(max)) {
                    min = 'a';
                } else {
                    min = 'A';
                }
            }
            if(s1[i + 1] != '\0') {
                max = s1[i + 1] - 1;
            } else {
                if(isdigit(s1[i - 1])) {
                    max = '9';
                } else if(islower(s1[i - 1])) {
                    max = 'z';
                } else {
                    max = 'Z';
                }
            }
            for(k = min; k <= max; k++) {
                s2[j++] = k;
            }
        } else {
            s2[j++] = s1[i];
        }
    }
    s2[j] = '\0';
}




