/*
 * 5-3. Write a pointer version of the function strcat that we showed in Chapter 2:
 * strcat(s,t) copies the string t to the end of s .
 *
 * wy-ei 2015.1.30
*/


#include <stdio.h>
#include <stdlib.h>

void strcat_(char *,char *);

int main(){
	char a[20]="hello ";
	char b[]="world!";

	strcat_(a,b);

	printf("%s\n",a);

	return EXIT_SUCCESS;
}

void strcat_(char *s,char *t){
	while(*s!='\0'){
		s++;
	}
	while(*t!='\0'){
		*s++=*t++;
	}
	*s='\0';
}




