/*
 * 7-4. Write a private version of scanf analogous to minprintf from the previous
 * section.
 *
 * wy-ei 2015.2.15
*/



#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>

void miniscanf(char* fmt,...);

#define MAXSTRING 1024
main() /* rudimentary calculator */
{
	int day,year;
	char month[20];
	miniscanf("%d %s %d",&year,month,&day);
	printf("%d/%s/%d\n",year,month,day);
	return 0;
}

void miniscanf(char* fmt,...){
	va_list ap;
	va_start(ap,fmt);
	char *p;
	int c;
	int ival,*pival;
	char cval,*pcval;
	float dval,*pdval;
	char sval[MAXSTRING],*psval;
	for(p=fmt;*p;p++){
		if(isspace(*p))
			continue;
		if(*p!='%'){
			while((c=getchar())!=EOF&&isspace(c));
			if(c!=*p){
				va_end(ap);
				return;
			}
			continue;
		}
		switch(*++p){
			case 'd':
				scanf("%d",&ival);
				pival=va_arg(ap,int *);
				*pival=ival;
				break;
			case 'f':
				scanf("%f",&dval);
				pdval=va_arg(ap,float *);
				*pdval=dval;
				break;
			case 's':
				scanf("%s",sval);
				psval=va_arg(ap,char *);
				strcpy(psval,sval);
				break;
			case 'c':
				cval=getchar();
				pcval=va_arg(ap,char *);
				*pcval=cval;
				break;
			default:
				break;
		}
	}
	va_end(ap);
}
