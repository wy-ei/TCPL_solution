/*
 * 6-1. Our version of getword does not properly handle underscores, string constants,
 * comments, or preprocessor control lines. Write a better version.
 *
 * wy-ei 2015.2.14
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>


struct key{
	char *word;
	int count;
};

struct key keytab[]={
	{"auto",0},
	{"break",0},
	{"case",0},
	{"char",0},
	{"const",0},
	{"continue",0},
	{"default",0},
	{"do",0}, 
	{"double",0},
	{"else",0},
	{"enum",0},
	{"extern",0},
	{"float",0},
	{"for",0},
	{"goto",0},
	{"if",0},
	{"int",0},
	{"long",0},
	{"register",0},
	{"return",0},
	{"short",0},
	{"signed",0},
	{"sizeof",0},
	{"static",0},
	{"struct",0},
	{"switch",0},
	{"typedef",0},
	{"union",0},
	{"unsigned",0},
	{"void",0},
	{"volatile",0},
	{"while",0}
};
#define MAXWORD 100

int getword(char *,int);
int binsearch(char *,struct key *,int);
int getch();
void ungetch();
void _qsort(struct key *,int left,int right);
void swap(char *a,char *b);

#define NKEYS (sizeof(keytab)/sizeof(keytab[0]))
#define BUFSIZE 1000
char buf[BUFSIZE];
int bufp=0;

int main(){
	int n;
	char word[MAXWORD];
	_qsort(keytab,0,NKEYS-1);  // sort key word tab
	while(getword(word,MAXWORD)!=EOF){
		if(isalpha(word[0])){
			if((n=binsearch(word,keytab,NKEYS))>=0){
				keytab[n].count++;
			}
		}
	}

	for(n=0;n<NKEYS;n++){
		if(keytab[n].count>0){
			printf("%-10s:%-4d\n",keytab[n].word,keytab[n].count);
		}
	}
	return 0;
}

int getch(){
	return bufp?buf[--bufp]:getchar();
}
void ungetch(int c){
	if(bufp==BUFSIZE){
		printf("ungetch:too many characters\n");
	}else{
		buf[bufp++]=c;
	}
}

int getword(char *word,int lim){
	char *w=word;
	int c;
	while(isspace(c=getch()))
	  ;
	if(c!=EOF){
		*w++=c;
	}
	if(c=='/'){
		if((c=getch())=='/'){   //if in comment //
			while(getch()!='\n')
			  ;
			c=getch();
		}else if(c=='*'){   // if  in comment  /* */
			char tmp1,tmp2;
			tmp1=getch();
			tmp2=getch();
			while(tmp1!='*'||tmp2!='/'){
			  tmp1=tmp2;
			  tmp2=getch();
			}
			c=getch();
		}else{            // not comment 
			ungetch(c);
			c='/';
		}
	}
	if(c=='\\'){      //if \"  ,delete those  
		char tmp;
		if((tmp=getch())!='\"'){
			ungetch(tmp);
		}
	}
	if(c=='\"'){    // if in double quote.  we should consider this  "abcd\"efg"  ,so I delete \" above.
		char tmp1,tmp2;
		tmp1=tmp2=getch();
		while(1){
			if(tmp1!='\\'&&tmp2=='\"')
			  break;
			tmp1=tmp2;
			tmp2=getch();
		}
	}
	
	if(!isalpha(c)&&c!='_'&&c!='#'){   //consider  _if_ or #if
		*w='\0';
		return c;
	}
	for(;--lim>0;w++){
		if(!isalnum(*w=getch())&&*w!='_'&&*w!='#'){
			ungetch(*w);
			break;
		}
	}
	*w='\0';

	return word[0];
}

int binsearch(char *word,struct key tab[],int n){
	int cond;
	int low,mid,high;
	low=0;
	high=n-1;
	while(low<=high){
		mid=(low+high)/2;
		if((cond=strcmp(word,tab[mid].word))>0){
			low=mid+1;
		}else if(cond<0){
			high=mid-1;
		}else{
			return mid;
		}
	}
	return -1;
}

void _qsort(struct key tab[],int left,int right){
	if(left<right){
		int i=left,j=right;
		char *tmp=tab[i].word;
		while(i<j){
			while(i<j&&strcmp(tab[j].word,tmp)>=0){
				j--;
			}
			if(i<j){
				tab[i++].word=tab[j].word;
			}
			while(i<j&&strcmp(tab[i].word,tmp)<0){
				i++;
			}
			if(i<j){
				tab[j--].word=tab[i].word;
			}
			tab[i].word=tmp;
			_qsort(tab,left,i-1);
			_qsort(tab,i+1,right);
		}
	}
}

void swap(char *a,char *b){
	char *tmp=a;
	a=b;
	b=tmp;
}

