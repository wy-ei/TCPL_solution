/*
 * 1-23. Write a program to remove all comments from a C program. Don't forget to
 * handle quoted strings and character constants properly. C comments don't nest.
 *
 * wy-ei 2015.1.21
 */

#include <stdio.h>
#define INCOMMENT     0
#define INSINGLEQOUTE 1
#define INDOUBLEQOUTE 2
#define INCODE        3

#define SLASH		  4
#define START		  5
void RmComment(FILE *);
int main(int args,char **argv){
	FILE *fp;
	if(args==1){
		fp=stdin;
		RmComment(fp);
	}
	else{
		while(args>1){
			++argv;
			--args;
			fp=fopen(*argv,"r");
			RmComment(fp);
			close(fp);
		}
	}
	return 0;
}
void RmComment(FILE *fp){
	int c;
	int state=INCODE;
	while((c=getc(fp))!=EOF){
		if(state==INCODE){
			if(c=='/'){ 
				state=INCOMMENT;
			}else if(c=='\''){
				state=INSINGLEQOUTE;
			}
			else if(c=='\"'){
				state=INDOUBLEQOUTE;
			}else{
				putchar(c);
			}
		}else if(state==INCOMMENT){
			if(c=='/'){
				int tmp;
				while((tmp=getc(fp))!='\n'&&tmp!=EOF)
				  ;
				if(tmp==EOF){
					return;
				}else{
					putchar('\n');
				}
			}else if(c=='*'){
				int tmp1,tmp2;
				tmp2=getc(fp);
				while((tmp1!='*'||tmp2!='/')&&tmp2!=EOF){
					tmp1=tmp2;
					tmp2=getc(fp);
				}
				if(tmp2==EOF){
					return;
				}
			}else{
				putchar('/');
				putchar(c);
			}
			state=INCODE;
		}else if(state==INDOUBLEQOUTE){
			int tmp1,tmp2;
			tmp2=c;
			int CLEAR = 0;
			while(tmp2!='\"'&&tmp2!=EOF){
				tmp1=tmp2;
				tmp2=getc(fp);
				if(tmp1=='\\'&&tmp2=='\\'){    //   str="abcd//"
					tmp1=tmp2=CLEAR;
				}else if(tmp1=='\\'&&tmp2=='\"'){  //  str="abcd/"efg"
					tmp1=tmp2=CLEAR;
				}
			}
			if(tmp2==EOF){
				return;
			}
			state=INCODE;
		}else if(state==INSINGLEQOUTE){
			int tmp1,tmp2;
			tmp2=c;
			int CLEAR = 0;
			while(tmp2!='\''&&tmp2!=EOF){
				tmp1=tmp2;
				tmp2=getc(fp);
				if(tmp1=='\\'&&tmp2=='\\'){    //   str="abcd//"
					tmp1=tmp2=CLEAR;
				}else if(tmp1=='\\'&&tmp2=='\''){  //  str="abcd/"efg"
					tmp1=tmp2=CLEAR;
				}
			}
			if(tmp2==EOF){
				return;
			}
			state=INCODE;
		}
	}
	return;
}
