/*
 * 1-19. Write a function reverse(s) that reverses the character string s . Use it to
 * write a program that reverses its input a line at a time.
 *
 * wy-ei 2015.1.18
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void reverse(char str[]);

int main(){
	char *str=NULL;
	int len;
	while(getline(&str,&len,stdin)!=-1){
		reverse(str);
		printf("%s",str);
	}
	free(str);
	return 0;
}

void reverse(char str[]){
	char tmp;
	int len=strlen(str);
	int low=0,high=len-2;   //str[len-1] is '\0' , str[len-2] is '\n'
	while(low<high){
		tmp=str[low];
		str[low]=str[high];
		str[high]=tmp;
		--high;
		++low;
	}
}
