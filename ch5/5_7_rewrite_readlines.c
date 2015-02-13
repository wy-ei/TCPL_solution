/*
 * 5-7. Rewrite readlines to store lines in an array supplied by main , rather than
 * calling alloc to maintain storage. How much faster is the program?
 *
 * wy-ei 2015.2.9
*/



#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 100    //no more than 5000 lines
#define MAXLEN 1000

char *lineptr[MAXLINES];   //an array for store pointer of string

int readlines(char *lineptr[],char *buf,int nlines);	//read mutil string
void writelines(char *lineptr[],int nlines); // print string

void _qsort(char *lineptr[],int left,int right);  //sort string
void _qsort1(char *lineptr[],int left,int right);  //sort string

int main(){
	int nlines;  //lines
	char buf[MAXLINES * MAXLEN];
	
	if((nlines = readlines(lineptr,buf,MAXLINES))>=0){
		_qsort1(lineptr,0,nlines-1);
		printf("-----after sort------\n");
		writelines(lineptr,nlines);
		return 0;
	}else{
		printf("error:input too big to sort\n");
		return 1;
	}
}

int _getline(char *,int);
char *alloc(int);

int readlines(char *lineptr[],char *buf,int maxlines){
	int len,nlines;  //string length , current lines
	char *p,line[MAXLEN]; // a pointer, array for store input
	
	size_t bufsize = MAXLEN*MAXLINES;
	int index=0;
	nlines = 0;
	p=buf;
	while((len = _getline(line,MAXLEN))>0&&index+len<bufsize){
		if(nlines>=maxlines)
			return -1;
		else{
			line[len-1]='\0';
			strcpy(p+index,line);
			lineptr[nlines++]=p+index;
			index+=len;
		}
	}
	return nlines;
}


char *alloc(int n){
	char *pt;
	pt=malloc(n);
	return pt;
}
void writelines(char *lineptr[],int nlines){
	int i;
	for(i=0;i<nlines;i++){
		printf("%s\n",lineptr[i]);
	}
}
void _qsort(char *v[],int left,int right){
	int i,last;
	void swap(char *v[],int i,int j);

	if(left>=right){
		return;
	}

	swap(v,left,(left+right)/2);
	last = left;
	for(i=left+1;i<=right;i++){
		if(strcmp(v[i],v[left])<0){
			swap(v,++last,i);
		}
	} 
	swap(v,left,last);
	_qsort(v,left,last-1);
	_qsort(v,last+1,right);
}
void _qsort1(char *v[],int left,int right){
	if(left<right){
		int i=left,j=right;
		char *temp=v[i];
		while(i<j){
			while(i<j&&strcmp(v[j],temp)>=0){
				j--;
			}
			if(i<j){
				v[i++]=v[j];
			}
			while(i<j&&strcmp(v[i],temp)<0){
				i++;
			}
			if(i<j){
				v[j--]=v[i];
			}
			v[i]=temp;
			_qsort(v,left,i-1);
			_qsort(v,i+1,right);
		}
	}
}
void swap(char *v[],int i,int j){
	char *temp;

	temp=v[i];
	v[i]=v[j];
	v[j]=temp;
}

int _getline(char *s,int limits){
	int i;
	int c;
	for(i=0;i<limits-1&&(c=getchar())!='\n'&&c!=EOF;i++){
		s[i]=c;
	}
	if(c=='\n'){
		i++;
	}
	s[i]='\0';
	return i;
}

