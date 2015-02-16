/*
 * 7-1. Write a program that converts upper case to lower or lower case to upper,
 * depending on the name it is invoked with, as found in argv[0] .
 *
 * wy-ei 2015.2.15
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc,char* argv[]){
	if(argc<2){
		printf("Usage:./a.out [tolower|toupper]\n");
		return 1;
	}
	int c;
	int (*func)(int);
	if(strcmp(argv[1],"tolower")==0){
		func=tolower;
	}else if(strcmp(argv[1],"toupper")==0){
		func=toupper;
	}else{
		printf("error:argument %s invalid\n",argv[1]);
		return 1;
	}
	while((c=getchar())!=EOF){
		putchar(func(c));
	}
	return 0;
}
