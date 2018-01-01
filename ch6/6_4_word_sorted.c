/*
 * 6-4. Write a program that prints the distinct words in its input sorted into decreasing
 * order of frequency of occurrence. Precede each word by its count.
 *
 * wy-ei 2015.2.15
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct Tnode {
    struct Tnode* left;
    struct Tnode* right;
    char *word;
    int count;
};

struct Tnode* Talloc();

struct Tnode* addtree(struct Tnode* root, char* word);
void printArray(struct Tnode**);
struct Tnode* treeSearch(struct Tnode* root, char* word);
struct Tnode* treeInsert(struct Tnode* root, char* word);
void treeMakeEmpty(struct Tnode* root);
int getword(char *word, int maxlen);

void treePrint(struct Tnode* root);
void treeToArray(struct Tnode** root, struct Tnode*** nodeArray);
#define BUFSIZE 100
char buf[BUFSIZE];
int  pbuf = 0;
int getch();
void ungetch(int c);

#define MAXLEN 100

int main() {
    struct Tnode* root = NULL;
    struct Tnode**  nodeArray = NULL;
    char word[MAXLEN];
    while(getword(word, MAXLEN) != EOF) {
        if(isalpha(word[0])) {
            root = addtree(root, word);
        }
    }
    //	treePrint(root);
    treeToArray(&root, &nodeArray);
    printArray(nodeArray);
    treeMakeEmpty(root);
    free(nodeArray);
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


struct Tnode* addtree(struct Tnode* root, char* word) {
    struct Tnode* searchtree = treeSearch(root, word);
    if(searchtree == NULL) {
        root = treeInsert(root, word);
    } else {
        searchtree->count++;
    }
    return root;
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
        root->count = 1;
    }
    int cond = strcmp(root->word, word);
    if(cond > 0) {
        root->left = treeInsert(root->left, word);
    } else if(cond < 0) {
        root->right = treeInsert(root->right, word);
    }

    return root;
}
void treeToArray(struct Tnode** root, struct Tnode*** array) {
    void treeCopyToArray(struct Tnode**, struct Tnode**);
    void _qsort(struct Tnode** , int, int);
    unsigned int countNode(struct Tnode*);
    unsigned int nodeNum = countNode(*root);
    struct Tnode** tmp = malloc(sizeof(struct Tnode*)*nodeNum); //create a array stort all the node
    treeCopyToArray(root, tmp);
    _qsort(tmp, 0, nodeNum - 1);
    *array = tmp;
}
void _qsort(struct Tnode** v , int left, int right) {
    if(left < right) {
        int i = left, j = right;
        struct Tnode* tmp = v[i];
        while(i < j) {
            while(i < j && v[j]->count < tmp->count) {
                j--;
            }
            if(i < j) {
                v[i++] = v[j];
            }
            while(i < j && v[i]->count >= tmp->count) {
                i++;
            }
            if(i < j) {
                v[j--] = v[i];
            }
        }
        v[i] = tmp;
        _qsort(v, left, i - 1);
        _qsort(v, i + 1, right);
    }
}
void treeCopyToArray(struct Tnode** src, struct Tnode** dst) {
    static unsigned int index = 0;
    if((*src) != NULL) {
        treeCopyToArray(&(*src)->left, dst);
        dst[index++] = *src;
        treeCopyToArray(&(*src)->right, dst);
    }
    dst[index] = NULL;
}
void treePrint(struct Tnode* root) {
    if(root == NULL) {
        return;
    }
    treePrint(root->left);
    printf("%s :%d", root->word, root->count);
    treePrint(root->right);
}

void printArray(struct Tnode** array) {
    int i = 0;
    while(array[i] != NULL) {
        printf("%-3d:%s\n", array[i]->count, array[i]->word);
        i++;
    }
}

unsigned int countNode(struct Tnode* root) {
    if(root == NULL) {
        return 0;
    } else {
        return countNode(root->left) + countNode(root->right) + 1;
    }
}
void treeMakeEmpty(struct Tnode* root) {
    if(root != NULL) {
        treeMakeEmpty(root->right);
        treeMakeEmpty(root->left);
        free(root->word);
    }
}

int getword(char *word, int maxlen) {
    int c;
    while(isspace(c = getch()))
        ;
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
