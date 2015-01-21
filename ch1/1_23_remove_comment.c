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
	int commentType;
	char lastChar=' ';
	while((c=getc(fp))!=EOF){
		if(state==INCODE){
			if(c=='/'){
				int tmp;
				tmp=getc(fp);
				if(tmp=='/'){        //  //
					state=INCOMMENT;
					commentType=SLASH;
				}
				else if(tmp=='*'){    // /*  */
					state=INCOMMENT;
					commentType=START;
				}
				else{
					putchar(c);
					c=tmp;
				}
			}
			else if(c=='"'){
				state=INDOUBLEQOUTE;
			}
			else if(c=='\''){
				state=INSINGLEQOUTE;
			}
			else{
				putchar(c);
			}

		}
		if(state==INDOUBLEQOUTE){
			putchar(c);
			int tmp;
			while((tmp=getc(fp))!='"'){
				if(tmp==EOF){
					return;
				}
				putchar(tmp);
			}
			putchar(tmp);
			state=INCODE;
		}
		if(state==INSINGLEQOUTE){
			putchar(c);
			int tmp=getc(fp);
			if(tmp==EOF){
				return;
			}
			if(tmp=='\\'){  // '\n'  '\''
				putchar(tmp);
				int i=2;
				while(i--){
					tmp=getc(fp);
					if(tmp==EOF){
						return;
					}
					putchar(tmp);
				}
			}
			else{    //  'a'
				putchar(tmp);
				tmp=getc(fp);
				if(tmp==EOF){
					return;
				}
				putchar(tmp);
			}
			state=INCODE;
		}
		if(state==INCOMMENT){
			if(commentType==START){
				int tmp;
				char c1,c2;
				while((tmp=getc(fp))!=EOF){
					c1=c2;
					c2=tmp;
					if(c1=='*'&&c2=='/'){
						break;
					}
				}
				state=INCODE;
			}
			if(commentType==SLASH){
				int tmp;
				while((tmp=getc(fp))!=EOF){
					if(tmp=='\n'){
						putchar(tmp);  // print a '\n'
						break;
					}
				}
				state=INCODE;
			}
		}		
	}
	return;
}
