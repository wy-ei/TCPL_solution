/*
 * 6-5. Write a function undef that will remove a name and definition from the table
 * maintained by lookup and install .
 *
 * wy-ei 2015.2.15
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASHSIZE 101


struct nlist {
    struct nlist* next;
    char *name;
    char *defn;
};

struct nlist* hashtab[HASHSIZE];
int hash(char *s);
struct nlist* lookup(char *s);
struct nlist* install(char* name, char* defn);
void undef(char* name);

#define BUFSIZE 100
char buf[BUFSIZE];
int  pbuf = 0;
int getch();
void ungetch(int);
#define MAXLEN 100
int getword(char* word, int maxlen);
int main() {
    char word1[MAXLEN];
    char word2[MAXLEN];
    struct nlist* np;
    while(getword(word1, MAXLEN) != EOF) {
        if(word1[0] == '#') {
            if(strcmp(word1, "#define") == 0) {
                if(getword(word1, MAXLEN) == EOF || getword(word2, MAXLEN) == EOF) { //get name and defn
                    break;
                }
                install(word1, word2);
            } else if(strcmp(word1, "#undef") == 0) {
                if(getword(word1, MAXLEN) == EOF) {
                    break;
                }
                undef(word1);
            } else {
                printf("%s", word1);
            }
        } else if((np = lookup(word1)) != NULL) {
            printf("%s", np->defn);
        } else {
            printf("%s", word1);
        }
    }


}

int getch() {
    return pbuf ? buf[--pbuf] : getchar();
}
void ungetch(int c) {
    if(pbuf < BUFSIZE) {
        buf[pbuf++] = c;
    } else {
        printf("ungetch:buf is full!\n");
    }
}
int getword(char* w, int maxlen) {
    int c;
    while(isspace(c = getch())) {
        putchar(c);
    }


    if(c == '/') {
        if((c = getch()) == '/') { //if in comment //
            while(getch() != '\n')
                ;
            putchar('\n');
            c = getch();
        } else if(c == '*') { // if  in comment  /* */
            char tmp1, tmp2;
            tmp1 = getch();
            tmp2 = getch();
            while(tmp1 != '*' || tmp2 != '/') {
                tmp1 = tmp2;
                tmp2 = getch();
            }
            c = getch();
        } else {           // not comment
            ungetch(c);
            c = '/';
        }
    }
    if(c == '\\') {   //if \"  ,delete those
        char tmp;
        if((tmp = getch()) != '\"') {
            ungetch(tmp);
        }
    }
    if(c == '\"') { // if in double quote.  we should consider this  "abcd\"efg"  ,so I delete \" above.
        char tmp1, tmp2;
        tmp1 = tmp2 = getch();
        while(1) {
            if(tmp1 != '\\' && tmp2 == '\"')
                break;
            tmp1 = tmp2;
            tmp2 = getch();
        }
    }

    if(c != EOF) {
        *w++ = c;
    }

    if(!isalnum(c) && c != '#') {
        *w = '\0';
        return c;
    }
    for(; --maxlen; w++) {
        if(!isalnum(*w = getch()) && *w != '#') {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return w[0];
}

int hash(char* s) {
    unsigned hashval = 0;
    while(*s != '\0') {
        hashval = hashval * 31 + *s;
        s++;
    }
    return hashval % HASHSIZE;
}

struct nlist* lookup(char* s) {
    struct nlist* np;
    for(np = hashtab[hash(s)]; np != NULL; np = np->next) {
        if(strcmp(s, np->name) == 0) {
            return np;
        }
    }
    return NULL;
}
struct nlist* install(char* name, char* defn) {
    struct nlist* np;
    unsigned hashval;
    if((np = lookup(name)) == NULL) {
        np = malloc(sizeof(struct nlist));
        if(np == NULL || (np->name = strdup(name)) == NULL) {
            return NULL;
        }
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else {
        free(np->defn);
    }
    if((np->defn = strdup(defn)) == NULL) {
        return NULL;
    }
    return np;
}
void undef(char* name) {
    struct nlist* np;
    if((np = lookup(name)) == NULL) {
        return;
    } else {
        unsigned hashval = hash(name);
        struct nlist* tmp = hashtab[hashval];
        while(tmp != np && tmp->next != np) {
            tmp = tmp->next;
        }
        tmp->next = np->next;
        free(np->name);
        free(np->defn);
    }
}


