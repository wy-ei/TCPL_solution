/*
 * 1-16. Revise the main routine of the longest-line program so it will correctly print
 * the length of arbitrary long input lines, and as much as possible of the text.
 *
 * wy-ei 2015.1.18
*/

#include <stdio.h>

#define MAXLINE 1000


int my_getline(char line[],int maxlen);
void copy(char to[],char from[]);


int main(){
	char line[MAXLINE];
	char longest[MAXLINE];
	int	 len;
	int  lineLength=0;
	int  max=0;
	while((len=my_getline(line,MAXLINE))>0){
		if(len==MAXLINE-1){
			if(line[MAXLINE-2]!='\n'){  //no new line
				lineLength+=len;
				continue;
			}
		}
		else{
			lineLength+=len;
		}
		if(lineLength>max){
			max=lineLength;
		}
		lineLength=0;
	}
	printf("the length of longest line is :%d\n",max);
	return 0;
}

int my_getline(char s[],int len){
	int i,c;
	for(i=0;i<len-1&&(c=getchar())!=EOF&&c!='\n';i++){
		s[i]=c;
	}
	if(c=='\n'){
		s[i]==c;
		i++;
	}
	s[i]='\0';

	return i;
}

void copy(char to[],char from[]){
	int i=0;
	while((to[i]=from[i])!='\0')
	  ++i;
}
