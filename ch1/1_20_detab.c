/*
 * 1-20. Write a program detab that replaces tabs in the input with the proper number
 * of blanks to space to the next tab stop. Assume a fixed set of tab stops, say every n columns.
 * Should n be a variable or a symbolic parameter?
 *
 * wy-ei 2015.1.20
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define  N 4

char* detab(char *str);

int main(){
	char *line=NULL;
	char *newline;
	int len;
	while(getline(&line,&len,stdin)!=-1){
		newline = detab(line);
		printf("%s",newline);
		free(newline);
	}
	free(line);
	return 0;
}
char* detab(char *str){
	int len=0,num=0;
	int i=0;
	char c;
	while((c=str[i])!='\0'){
		if(c=='\t'){
			num++;
		}
		len++;
		i++;
	}
	char *newline;
	newline=(char *)malloc(len+(N-1)*num+1);   //use four blank replace one tab
	if(newline==NULL){
		fprintf(stderr,"can't malloc space\n");
	}
	i=0;
	int j=0;		//index of newline
	while((c=str[i])!='\0'){
		if(c=='\t'){
			int k;
			for(k=0;k<N;k++){
				newline[j]=' ';
				++j;
			}
		}
		else{
			newline[j]=str[i];
			++j;
		}
		++i;
	}
	newline[j]='\0';
	return newline;
}

/*
 * test method:  cat 1_20_detab.c | ./a.out | ./visible
 *
 * ./visable -- gcc 1_10_visible_unvisible_symbol.c  -o visible
 *
*/ 
