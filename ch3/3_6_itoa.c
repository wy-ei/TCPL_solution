/*
 * 3-6. Write a version of itoa that accepts three arguments instead of two. The third
 * argument is a minimum field width; the converted number must be padded with blanks on the
 * left if necessary to make it wide enough.
 *
 * wy-ei 2015.1.22
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void itoa(int n,char *s,int m);
void reverse(char *s);
int main(){
	int n=INT_MIN;
	int m=30;
	char s[50];
	itoa(n,s,m);
	printf("result:%s\n",s);
	
	return EXIT_SUCCESS;
}
void reverse(char *s){
	char c;
	int i,j=0;
	while(s[j]!='\0'){
		j++;
	}
	for(i=0,j-=1;i<j;i++,j--){
		c=s[i];
		s[i]=s[j];
		s[j]=c;
	}
}


void itoa(int n,char *s,int m){
	int sign,i;
	i=0;
	do{
		s[i++]=abs(n%10)+'0';
	}while((n/=10)!=0);
	if(sign<0){
		s[i++]='-';
	}
	for(;i<m;i++){
		s[i]=' ';
	}
	s[i]='\0';
	reverse(s);
}
