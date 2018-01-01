/*
 * 6-2. Write a program that reads a C program and prints in alphabetical order each
 * group of variable names that are identical in the first 6 characters, but different somewhere
 * thereafter. Don't count words within strings and comments. Make 6 a parameter that can be
 * set from the command line.
 *
 * wy-ei 2015.2.14
*/




#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct Tnode {
    char *word;
    int count;
    struct Tnode *left;
    struct Tnode *right;
};

#define MAXWORD 100

int getword(char *, int);
int getch();
void ungetch();

struct Tnode * addtree(struct Tnode *, char *);
void treePrint(struct Tnode *);
struct Tnode* treeInsert(struct Tnode*, char *);
struct Tnode* treeSearch(struct Tnode*, char *);
struct Tnode* talloc();
char* _strdup(char *);
#define NKEYS (sizeof(keytab)/sizeof(keytab[0]))
#define BUFSIZE 1000
char buf[BUFSIZE];
int bufp = 0;

int main() {
    char word[MAXWORD];
    struct Tnode *root;
    root = NULL;
    while(getword(word, MAXWORD) != EOF) {
        if(isalpha(word[0]) || word[0] == '_') {
            root = addtree(root, word);
        }
    }
    treePrint(root);
    return 0;
}

int getch() {
    return bufp ? buf[--bufp] : getchar();
}
void ungetch(int c) {
    if(bufp == BUFSIZE) {
        printf("ungetch:too many characters\n");
    } else {
        buf[bufp++] = c;
    }
}

int getword(char *word, int lim) {
    char *w = word;
    int c;
    while(isspace(c = getch()))
        ;
    if(c != EOF) {
        *w++ = c;
    }
    if(c == '/') {
        if((c = getch()) == '/') { //if in comment //
            while(getch() != '\n')
                ;
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

    if(!isalpha(c) && c != '_') { // consider _var
        *w = '\0';
        return c;
    }

    for(; --lim > 0; w++) {
        if(!isalnum(*w = getch()) && *w != '_') {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';

    return word[0];
}


struct Tnode* talloc() {
    return (struct Tnode*)malloc(sizeof(struct Tnode));
}
char*_strdup(char *s) {
    char *p;
    p = malloc(sizeof(strlen(s)) + 1);
    if(p != NULL) {
        strcpy(p, s);
    }
    return p;
}
struct Tnode* addtree(struct Tnode *root, char *word) {
    struct Tnode* t;
    t = treeSearch(root, word);
    if(t == NULL) {
        root = treeInsert(root, word);
    } else {
        t->count++;
    }
    return root;
}

struct Tnode* treeSearch(struct Tnode *root, char *word) {
    if(root == NULL) {
        return NULL;
    }
    int result;
    if((result = strcmp(root->word, word)) > 0) {
        return treeSearch(root->left, word);
    } else if(result < 0) {
        return treeSearch(root->right, word);
    } else {
        return root;
    }
}



struct Tnode* treeInsert(struct Tnode* root, char *word) {
    if(root == NULL) {
        root = talloc();
        root->word = _strdup(word);
        root->count = 1;
        root->left = root->right = NULL;
    }
    int result;
    if((result = strcmp(root->word, word)) > 0) {
        root->left = treeInsert(root->left, word);
    } else if(result < 0) {
        root->right = treeInsert(root->right, word);
    }

    return root;
}

void treePrint(struct Tnode* root) {
    static char GroupName = 0;
    if(root != NULL) {
        treePrint(root->left);
        if(GroupName != root->word[0]) {
            GroupName = root->word[0];
            printf("----%c----\n", root->word[0]);
        }
        printf("%-2d:%s\n", root->count, root->word);
        treePrint(root->right);
    }
}
