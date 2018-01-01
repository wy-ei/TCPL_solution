/*
 * 6-3. Write a cross-referencer that prints a list of all words in a document, and for
 * each word, a list of the line numbers on which it occurs. Remove noise words like ``the,''
 * ``and,'' and so on.
 *
 * wy-ei 2015.2.14
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


struct Lnode {
    int node;
    struct Lnode *next;
};
struct Tnode {
    struct Tnode* left;
    struct Tnode* right;
    char *word;
    struct Lnode* lineNum;
};

struct Tnode* Talloc();
struct Lnode* Lalloc();

struct Tnode* addtree(struct Tnode* root, char* word);
void treePrint(struct Tnode* root);
struct Tnode* treeSearch(struct Tnode* root, char* word);
struct Tnode* treeInsert(struct Tnode* root, char* word);
void treeMakeEmpty(struct Tnode* root);
int getword(char *word, int maxlen);
#define BUFSIZE 100
char buf[BUFSIZE];
int  pbuf = 0;
int getch();
void ungetch(int c);

#define MAXLEN 100
int currentLine = 1;

int main() {
    struct Tnode* root = NULL;

    char word[MAXLEN];
    while(getword(word, MAXLEN) != EOF) {
        if(isalpha(word[0])) {
            root = addtree(root, word);
        }
    }
    treePrint(root);
    treeMakeEmpty(root);
    return 0;
}

int getch() {
    return pbuf ? buf[--pbuf] : getchar();
}
void ungetch(int c) {
    if(pbuf < BUFSIZE) {
        buf[pbuf++] = c;
    } else {
        printf("ungetch:buf is full\n");
    }
}

struct Tnode* Talloc() {
    return (struct Tnode*)malloc(sizeof(struct Tnode));
}

struct Lnode* Lalloc() {
    return (struct Lnode*)malloc(sizeof(struct Lnode));
}

struct Tnode* addtree(struct Tnode* root, char* word) {
    struct Tnode* searchtree = treeSearch(root, word);
    if(searchtree == NULL) {
        root = treeInsert(root, word);
    } else {
        struct Lnode* tmp;
        tmp = Lalloc();
        tmp->node = currentLine;
        tmp->next = searchtree->lineNum->next;
        searchtree->lineNum->next = tmp;
    }
    return root;
}
void treePrint(struct Tnode* root) {
    if(root == NULL) {
        return;
    }
    treePrint(root->left);
    printf("%s :", root->word);
    struct Lnode* tmp = root->lineNum->next;
    while(tmp != NULL) {
        printf("%d ", tmp->node);
        tmp = tmp->next;
    }
    putchar('\n');
    treePrint(root->right);
}
struct Tnode* treeSearch(struct Tnode* root, char *word) {
    if(root == NULL) {
        return NULL;
    }
    int cond = strcmp(root->word, word);
    if(cond > 0) {
        return treeSearch(root->left, word);
    } else if(cond < 0) {
        return treeSearch(root->right, word);
    } else {
        return root;
    }
}

struct Tnode* treeInsert(struct Tnode* root, char *word) {
    if(root == NULL) {
        root = Talloc();
        root->left = root->right = NULL;
        root->word = strdup(word);
        root->lineNum = Lalloc();
        struct Lnode* tmp = Lalloc();
        root->lineNum->next = tmp;
        tmp->node = currentLine;
        tmp->next = NULL;
    }
    int cond = strcmp(root->word, word);
    if(cond > 0) {
        root->left = treeInsert(root->left, word);
    } else if(cond < 0) {
        root->right = treeInsert(root->right, word);
    }

    return root;
}

void treeMakeEmpty(struct Tnode* root) {
    if(root != NULL) {
        treeMakeEmpty(root->right);
        treeMakeEmpty(root->left);
        free(root->word);
        struct Lnode* tmp;
        while(root->lineNum != NULL) {
            tmp = root->lineNum;
            root->lineNum = root->lineNum->next;
            free(tmp);
        }
    }
}

int getword(char *word, int maxlen) {
    int c;
    while(isspace(c = getch())) {
        if(c == '\n') {
            currentLine++;
        }
    }
    if(c != EOF) {
        *word++ = c;
    }
    if(!isalpha(c)) {
        *word = '\0';
        return c;
    }
    for(; --maxlen; word++) {
        if(!isalnum(*word = getch())) {
            ungetch(*word);
            break;
        }
    }
    *word = '\0';
    return word[0];
}
