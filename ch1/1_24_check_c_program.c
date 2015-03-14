/*
 * 1-24. Write a program to check a C program for rudimentary syntax errors like
 * unmatched parentheses, brackets and braces. Don't forget about quotes, both single and
 * double, escape sequences, and comments. (This program is hard if you do it in full
 * generality.)
 *
 * wy-ei 2015.1.21
*/

#include <stdio.h>

#define INCOMMENT     0
#define INSINGLEQOUTE 1
#define INDOUBLEQOUTE 2
#define INCODE        3

void checkSyntax(FILE *);
void error(const char *,int);

int main(int args,char **argv){
	FILE *fp;
	if(args==1){
		fp=stdin;
		checkSyntax(fp);
	}
	else{
		while(args>1){
			++argv;
			--args;
			fp=fopen(*argv,"r");
			checkSyntax(fp);
			close(fp);
		}
	}
	return 0;
}
void checkSyntax(FILE *fp){
	int c;
	int state=INCODE;
	int  linenum=0;
	int nparenthes,nbracket,nbrace;
	nparenthes=nbracket=nbrace=0;
	while((c=getc(fp))!=EOF){
		if(state==INCODE){
			if(c=='\n'){
				linenum++;
			}
			else if(c=='('){
				nparenthes++;
			}else if(c==')'){
				if(nparenthes==0){
					error("Unbalanced parenthes",linenum);
				}
				nparenthes--;
			}
			else if(c=='['){
				nbracket++;
			}
			else if(c==']'){
				if(nbracket==0){
					error("Unbalanced brackets",linenum);
				}
				nbracket--;
			}else if(c=='{'){
				nbrace++;
			}else if(c=='}'){
				if(nbrace==0){
					error("Unbalanced braces",linenum);
				}
				nbrace--;
			}else if(c=='/'){
				state=INCOMMENT;
			}else if(c=='\"'){
				state = INDOUBLEQOUTE;
			}else if(c=='\''){
				state = INSINGLEQOUTE;
			}
		}else if(state==INCOMMENT){
			if(c=='/'){
				int tmp;
				while((tmp=getc(fp))!='\n'&&tmp!=EOF)
				  ;
				if(tmp==EOF){
					return;
				}
			}else if(c=='*'){
				int tmp1,tmp2;
				tmp2=getc(fp);
				while((tmp1!='*'||tmp2!='/')&&tmp2!=EOF){
					tmp1=tmp2;
					tmp2=getc(fp);
				}
				if(tmp2==EOF){
					error("Unbalanced Comment",linenum);
				}
			}
			state=INCODE;
		}
		else if(state==INDOUBLEQOUTE){
			int tmp1,tmp2;
			tmp2=c;
			int CLEAR = 0;
			while(tmp2!='\"'&&tmp2!=EOF){
				tmp1=tmp2;
				tmp2=getc(fp);
				if(tmp2=='\n'){
					linenum++;
				}
				if(tmp1=='\\'&&tmp2=='\\'){    //   str="abcd\\"
					tmp1=tmp2=CLEAR;
				}else if(tmp1=='\\'&&tmp2=='\"'){  //  str="abcd/"efg"
					tmp1=tmp2=CLEAR;
				}
			}
			if(tmp2==EOF){
				error("Unbalance double Quote",linenum);
			}
			state=INCODE;
		}
		else if(state==INSINGLEQOUTE){
			int tmp1,tmp2;
			tmp2=c;
			int CLEAR = 0;
			while(tmp2!='\''&&tmp2!=EOF){
				tmp1=tmp2;
				tmp2=getc(fp);
				if(tmp2=='\n'){
					linenum++;
				}
				if(tmp1=='\\'&&tmp2=='\\'){    //   str="abcd\\"
					tmp1=tmp2=CLEAR;
				}else if(tmp1=='\\'&&tmp2=='\''){  //  str="abcd\"efg"
					tmp1=tmp2=CLEAR;
				}
			}
			if(tmp2==EOF){
				error("Unbalance single Quote",linenum);
			}
			state=INCODE;
		}		
	}

	if(nparenthes!=0){
		error("Unbalanced parenthes",linenum);
	}
	if(nbracket!=0){
		error("Unbalanced brackets",linenum);
	}
	if(nbrace!=0){
		error("Unbalanced braces",linenum);
	}
	return;
}

void error(const char *errinfo,int num){
	fprintf(stderr,"%s:%d\n",errinfo,num);
}
