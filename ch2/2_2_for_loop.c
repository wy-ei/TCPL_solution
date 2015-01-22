/*
 * 2-2. Write a loop equivalent to the for loop above without using && or || .
 *
 * wy-ei 2015.1.21
*/

#include <stdio.h>
#define MAXSIZE  1024
int main(){
	char line[MAXSIZE];

	int i;
	int c;
	for(i=0;i<MAXSIZE-1?((c=getchar())!=EOF?c!='\n':0):0;++i){
		line[i]=c;
	}
	if(c=='\n'){
		line[i]=c;
		++i;
	}
	line[i]='\0';
	printf("%s\n",line);
	return 0;
}
	
