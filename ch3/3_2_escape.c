/*
 * 3-2. Write a function escape(s,t) that converts characters like newline and tab
 * into visible escape sequences like \n and \t as it copies the string t to s . Use a switch . Write
 * a function for the other direction as well, converting escape sequences into the real characters.
 *
 * wy-ei 2015.1.22
 */

#include <stdio.h>
#include <stdlib.h>
void escape(char *s, char *t);

void unescape(char *s, char *t);

int main() {
    char input[] = "\\\\\\a\\bcde\\fghijkim\\nopqrs\\tu\\vwsyz";
    char t[50] = {0};
    char s[50] = {0};

    printf("origin:      %s\n", input);
    unescape(s, input);

    printf("unvisible:   %s\n", s);

    escape(t, s);

    printf("visible:     %s\n", t);

    return EXIT_SUCCESS;
}

void escape(char *s, char *t) {
    int i = 0, j = 0;
    while(t[i++] != '\0') {
        switch(t[i]) {
        case '\a':
            s[j++] = '\\';
            s[j++] = 'a';
            break;
        case '\b':
            s[j++] = '\\';
            s[j++] = 'b';
            break;
        case '\f':
            s[j++] = '\\';
            s[j++] = 'f';
            break;
        case '\n':
            s[j++] = '\\';
            s[j++] = 'n';
            break;
        case '\r':
            s[j++] = '\\';
            s[j++] = 'r';
            break;
        case '\\':
            s[j++] = '\\';
            s[j++] = '\\';
            break;
        case '\t':
            s[j++] = '\\';
            s[j++] = 't';
            break;
        case '\v':
            s[j++] = '\\';
            s[j++] = 'v';
            break;
        default:
            s[j++] = t[i];
            break;
        }
    }
}
void unescape(char *s, char *t) {
    int i = 0, j = 0;
    while(t[i] != '\0') {
        if(t[i] == '\\') {
            i++;
            switch(t[i]) {
            case '\\':
                s[j++] = '\\';
                break;
            case 'n':
                s[j++] = '\n';
                break;
            case 'a':
                s[j++] = '\a';
                break;
            case 'b':
                s[j++] = '\b';
                break;
            case 'f':
                s[j++] = '\f';
                break;
            case 'r':
                s[j++] = '\r';
                break;
            case 't':
                s[j++] = '\t';
                break;
            case 'v':
                s[j++] = '\v';
                break;
            default:
                printf("invalid %c(0x%02x)\n", t[i], t[i]);
                break;
            }
        } else {
            s[j++] = t[i];
        }
        i++;
    }
}

