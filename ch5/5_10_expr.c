/*
 * 5-10. Write the program expr , which evaluates a reverse Polish expression from the
 * command line, where each operator or operand is a separate argument. For example,
 * expr 2 3 4 + *
 * evaluates 2 * (3+4).
 *
 * wy-ei 2015.2.9
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


struct node {
    int *element;
    int top;
    int capacity;
};

typedef struct node *stack;
typedef struct node node;

void init(stack	, int capacity);
void push(stack, int n);
int pop(stack);


int main(int argc, char *argv[]) {
    if(argc == 1) {
        printf("Usage:expr operand\n");
        return EXIT_SUCCESS;
    }
    stack operand = malloc(sizeof(node));
    char operator[100];
    int index = 0;

    init(operand, 100);
    int c;
    while(--argc) {
        c = (*++argv)[0];
        if(isdigit(c)) {
            push(operand, c - '0');
        } else {
            operator[index++] = c;
        }
    }

    int i;
    int temp;
    for(i = 0; i < index; i++) {
        switch(operator[i]) {
        case '+':
            push(operand, pop(operand) + pop(operand));
            break;
        case '-':
            temp = pop(operand);
            push(operand, pop(operand) - temp);
            break;
        case '*':
            push(operand, pop(operand)*pop(operand));
            break;
        case '/':
            temp = pop(operand);
            push(operand, pop(operand) / temp);
            break;
        default:
            printf("error:unknown signal %c.\n", operator[i]);
        }
    }
    printf("result:%d.\n", pop(operand));

    return EXIT_SUCCESS;
}



void init(stack s, int capacity) {
    s->top = 0;
    s->element = malloc(sizeof(int) * capacity);
    s->capacity = capacity;
}

void push(stack s, int n) {
    if(s->top < s->capacity) {
        s->element[s->top + 1] = n;
        s->top++;
    } else {
        printf("error:stack is full.\n");
    }
}
int pop(stack s) {
    if(s->top > 0) {
        int temp = s->element[s->top];
        s->top--;
        return temp;
    } else {
        printf("error:stack is empty.\n");
        exit(EXIT_FAILURE);
    }
}
