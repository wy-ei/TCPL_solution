/*
 * 5-15. Add the option -f to fold upper and lower case together, so that case
 * distinctions are not made during sorting; for example, a and A compare equal.
 * wy-ei 2015.2.10
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000
#define MAXLEN   1000

char *lineptr[MAXLINES];
int readlines(char *lineptr[],int nlines);
void writelines(char *lineptr[],int nlines);

void _qsort(void *lineptr[],int left,int right,int isreverse,int (*cmp)(void *,void *));
int numcmp(char *,char *);
int _getline(char *line,int maxlen);
int _strcmp(char *,char *);
int main(int argc,char *argv[]){
	int nlines;  /*number of input lines read*/
	int numeric=0;
	int reverse=0;
	int ignoreCase=0;
	while(argc>1){
		argc--;
		argv++;
		if(strcmp(*argv,"-n")==0){
			numeric=1;
		}else if(strcmp(*argv,"-r")==0){
			reverse=1;
		}else if(strcmp(*argv,"-f")==0){
			ignoreCase=1;
		}
	}

	if((nlines=readlines(lineptr,MAXLINES))>0){
		_qsort((void **)lineptr,0,nlines-1,reverse,(int (*)(void *,void *))(numeric ? numcmp :ignoreCase? _strcmp:strcmp));
		writelines(lineptr,nlines);
		return 0;
	}else{
		printf("input:input too big to sort.\n");
		return 1;
	}
}


int readlines(char *lineptr[],int maxlines){
	char line[MAXLEN],*p;
	int len,nlines=0;
	while((len=_getline(line,MAXLEN))>0){
		if(nlines>maxlines||(p=malloc(len))==NULL){
			return -1;
		}else{
			line[len-1]='\0';  //delete newline
			strcpy(p,line);
			lineptr[nlines++]=p;
		}
	}
	return nlines;
}
int _getline(char *line,int lim){
	int i,c;
	for(i=0;i<lim-1&&(c=getchar())!=EOF&&c!='\n';i++){
		line[i]=c;
	}
	if(c=='\n'){
		line[i++]='\n';
	}
	line[i]='\0';
	return i;
}
void writelines(char *lineptr[],int nlines){
	int i;
	for(i=0;i<nlines;i++){
		printf("%s\n",lineptr[i]);
	}
}
void _qsort(void *v[],int left,int right,int isreverse,int (*cmp)(void *,void *)){
	int last,i;
	void swap(void *v[],int i,int j);
	if(left>=right){
		return;
	}
	swap(v,left,(left+right)/2);
	last=left;
	for(i=left+1;i<=right;i++){
		if(isreverse){
			if((*cmp)(v[i],v[left])>=0){
				swap(v,++last,i);
			}
		}else{
			if((*cmp)(v[i],v[left])<0){
				swap(v,++last,i);
			}
		}
	}
	swap(v,left,last);
	_qsort(v,left,last-1,isreverse,cmp);
	_qsort(v,last+1,right,isreverse,cmp);
}
void swap(void *v[],int i,int j){
	void *temp;
	temp=v[i];
	v[i]=v[j];
	v[j]=temp;
}
int numcmp(char *n1,char *n2){
	double f1,f2;
	f1=atof(n1);
	f2=atof(n2);
	if(f1<f2){
		return -1;
	}else if(f1>f2){
		return 0;
	}else{
		return 0;
	}
}

int _strcmp(char *src,char *dst){
	int ret;
	while(!(ret=tolower(*src)-tolower(*dst))&&*dst){
		++src,++dst;
	}
	if(ret<0){
		ret=-1;
	}else if(ret>0){
		ret=1;
	}
	return ret;
}

