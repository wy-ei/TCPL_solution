/*
 * 2-4. Write an alternative version of squeeze(s1,s2) that deletes each character in
 * s1 that matches any character in the string s2 .
 *
 * wy-ei 2015.1.22
*/

#include <stdio.h>
#include <stdlib.h>

void squeeze(char *, char *);

int main() {
    char *str1 = NULL, *str2 = NULL;
    int len1 = 0, len2 = 0;
    while(1) {
        printf("enter first string:");
        if(getline(&str1, &len1, stdin) == -1) {
            break;
        }
        printf("enter second string:");
        if(getline(&str2, &len2, stdin) == -1) {
            break;
        }
        squeeze(str1, str2);
        printf("result:%s\n", str1);
    }
    free(str1);
    free(str2);
    return 0;
}

void squeeze(char *s1, char *s2) {
    int i, j, k;
    int finded = 0;
    for(i = 0, j = 0; s1[i] != '\0'; i++) {
        k = 0;
        while(s2[k] != '\0') {
            if(s2[k] == s1[i]) {
                finded = 1;
                break;
            }
            k++;
        }
        if(finded == 0) { // if doesn't finded
            s1[j] = s1[i];
            j++;
        } else {          // if  finded
            finded = 0;
        }
    }
    s1[j] = '\0';
}



