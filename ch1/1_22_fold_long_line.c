/*
 * 1-22. Write a program to "fold" long input lines into two or more shorter lines after the 
 * last non-blank character that occurs before the n -th column of input. Make sure your program 
 * does something intelligent with very long lines, and if there are no blanks or tabs before the specified column.
 *
 * wy-ei 2015.1.21
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define FOLDLENGTH 20

void fold(char *line);
void print(char *beg,char *end);
int main(){
	int len;
	char *line=NULL;
	while(getline(&line,&len,stdin)!=-1){
		fold(line);
	}
	free(line);
	return 0;
}

void fold(char *line){
	char c;
	int len = strlen(line);
	char *begin=line,*end;

	while(FOLDLENGTH<len){    
		end=begin+(FOLDLENGTH-1);
		while(end!=begin){
			c=*end;
			if(c==' '||c=='\t'){    // find the index of last non-blank character
				--end;	
			}
			else{
				break;
			}
		}
		print(begin,end);
		begin+=FOLDLENGTH;
		len-=FOLDLENGTH;
	}
	end=begin+len;
	print(begin,end);
}
void print(char *beg,char *end){
	while(beg<=end){
		putchar(*beg);
		++beg;
	}
	if(*(end-1)!='\n'){     // last segment don't need a new line character,because there is a '\n' at the end
		putchar('\n');
	}
}
