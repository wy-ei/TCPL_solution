/*
 * 5-1. As written, getint treats a + or - not followed by a digit as a valid
 * representation of zero. Fix it to push such a character back on the input.
 *
 * wy-ei 2015.1.27
*/


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int getint(int *pn);

int main(){
	int a;

	while(getint(&a)!=EOF){
		printf("%d\n",*a);
	}

	return EXIT_SUCCESS;
}

#define MAXBUFSIZE  100

int getch();
void ungetch(int);

char buf[MAXBUFSIZE];
int bufp=0;

int getch(){
	return bufp>0?buf[--bufp]:getchar();
}

void ungetch(int ch){
	if(bufp<MAXBUFSIZE-1){
		buf[bufp]=ch;
		bufp++;
	}else{
		printf("error:buf is full.\n");
	}
}

int getint(int *pn){
}
