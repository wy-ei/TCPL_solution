/*
 * 5-4. Write the function strend(s,t) , which returns 1 if the string t occurs at the
 * end of the string s , and zero otherwise.
 *
 * wy-ei 2015.1.30
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strend(char *s,char *t);

int main(){
	char *a="hello,world!";
	char *b="world!";
	char *c="hello";

	printf("%d\n",strend(a,b));

	printf("%d\n",strend(a,c));

	return EXIT_SUCCESS;
}

int strend(char *s,char *t){
	char *tmp = s + (strlen(s) - strlen(t));
	while(*t){
		if(*tmp!=*t){
			return 0;
		}
		tmp++;
		t++;
	}
	return 1;
}

