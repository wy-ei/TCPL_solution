/*
 * 4-3. Given the basic framework, it's straightforward to extend the calculator. Add
 * the modulus (%) operator and provisions for negative numbers.
 *
 * wy-ei 2015.1.22
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXOP  100   /* max size of operand or operation */
#define NUMBER '0'   /* signal that a number was found */


#define BUFSIZE  100
char buf[BUFSIZE];
int bufp=0;

#define MAXVAL 100
double val[MAXVAL];
int sp=0;

int getop(char *);
void push(double);
double pop();
int getch();
void ungetch(int);


int main(){
	int type;
	double op2;
	char s[MAXOP];

	while((type=getop(s))!=EOF){
		switch(type){
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				push(pop()+pop());
				break;
			case '*':
				push(pop()*pop());
				break;
			case '-':
				op2=pop();
				push(pop()-op2);
				break;
			case '/':
				op2=pop();
				if(op2!=0){
					push(pop()/op2);
				}else{
					printf("error:zero divisor\n");
				}
				break;
			case '%':
				op2=pop();
				push(fmod(pop(),op2));
				break;
			case '\n':
				printf("%.8g\n",pop());
				break;
			default:
				printf("unknown command %s\n",s);
				break;
		}
	}
	return EXIT_SUCCESS;
}


void push(double f){
	if(sp<MAXVAL){
		val[sp++]=f;
	}else{
		printf("error:stack full,can't push %g\n",f);
	}
}

double pop(){
	if(sp>0){
		return val[--sp];
	}else{
		printf("error:stack empty,can't pop\n");
		return 0.0;
	}
}

int getch(){
	return (bufp>0)?buf[--bufp]:getchar();
}

void ungetch(int c){
	if(bufp>=BUFSIZE){
		printf("ungetch: too many characters\n");
	}else{
		buf[bufp++]=c;
	}
}
int getop(char *s){
	int i,c;
	while((s[0]=c=getch())==' '||c=='\t')
	  ;
	s[1]='\0';
	if(!isdigit(c)&&c!='.'&&c!='-'){
		return c;
	}
	i=0;
	
	if(c=='-'){
		int next=getch();
		if(!isdigit(next)&&next!='.'){
			return c;
		}
		c=next;
	}else{
		c=getch();
	}
	
	while(isdigit(s[++i]=c))
		c=getch();

	if(c=='.'){
		while(isdigit(s[++i]=c=getch()))
		  ;
	}
	s[i]='\0';
	if(c!=EOF){
		ungetch(c);
	}

	return NUMBER;
}
