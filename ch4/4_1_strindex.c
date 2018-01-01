/*
 * 4-1. Write the function strindex(s,t) which returns the position of the rightmost
 * occurrence of t in s , or -1 if there is none.
 *
 * wy-ei 2015.1.22
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int strindex(char *s, char *t);

int main() {
    char *s = NULL;
    char *t = NULL;
    int len1, len2;
    int pos;
    while(1) {
        printf("enter string s:");
        if(getline(&s, &len1, stdin) == -1) {
            break;
        }
        printf("enter string t:");
        if(getline(&t, &len2, stdin) == -1) {
            break;
        }
        t[strlen(t) - 1] = '\0'; // there are two characteres int the end '\n' and '\0', if you get this string by getline.
        pos = strindex(s, t);
        if(pos == -1) {
            printf("never finded.\n");
        } else {
            printf("position:%d\n", pos);
        }
    }
    free(s);
    free(t);
    return EXIT_SUCCESS;
}

int strindex(char *s, char *t) {
    int i, j, k;
    i = j = k = 0;

    for(i = strlen(s) - strlen(t); i >= 0; i--) {
        for(j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if(t[k] == '\0') {
            return i;
        }
    }
    return -1;
}




