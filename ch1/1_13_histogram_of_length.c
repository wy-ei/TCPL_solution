/*
 * Write a program to print a histogram of the lengths of words in its input. It is
 * easy to draw the histogram with the bars horizontal; a vertical orientation is more challengin
 *
 * wy-ei 2015.1.18
*/

#include <stdio.h>

const int in=0,out=1;

int main(){
	int state = out;
	int c;
	int len=0;
	while((c=getchar())!=EOF){
		if(c=='\n'||c=='\t'||c==' '){
			if(state == in){
				int i;
				for(i=0;i<len;i++){
					putchar('=');
				}
				putchar('\n');
				state=out;
				len=0;
			}
		}
		else{
			if(state==out){
				state=in;
			}
			len++;
			putchar(c);
		}
	}
	return 0;
}




