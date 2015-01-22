/*
 * 2-5. Write the function any(s1,s2) , which returns the first location in a string s1
 * where any character from the string s2 occurs, or -1 if s1 contains no characters from s2 .
 * (The standard library function strpbrk does the same job but returns a pointer to the
 * location.)
 *
 * wy-ei 2015.1.22
*/

#include <stdio.h>
#include <stdlib.h>

int any(char *,char *);

int main(){
	char *str1=NULL,*str2=NULL;
	int len1=0,len2=0;
	int pos;
	while(1){
		printf("enter first string:");
		if(getline(&str1,&len1,stdin)==-1){
			break;
		}
		printf("enter second string:");
		if(getline(&str2,&len2,stdin)==-1){
			break;
		}
		pos = any(str1,str2);
		if(pos==-1){
			printf("never finded!\n");
		}else{
			printf("position:%d character:%c\n",pos+1,str1[pos]);
		}
	}
	free(str1);
	free(str2);
	return 0;
}

int any(char *str1,char *str2){
	int i,j;
	int c;
	for(i=0;(c=str1[i])!='\0';i++){
		j=0;
		while(str2[j]!='\0'){
			if(c==str2[j]){
				return i;
			}
			j++;
		}	
	}
	return -1;
}


		


