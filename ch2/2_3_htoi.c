/*
 * 2-3. Write a function htoi(s) , which converts a string of hexadecimal digits
 * (including an optional 0x or 0X ) into its equivalent integer value. The allowable digits are 0
 * through 9 , a through f , and A through F .
 *
 * wy-ei 2015.1.21
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

long htoi(char *);
int main(){
	char *str=NULL;
	int len;

	while(getline(&str,&len,stdin)!=-1){
		printf("%ld\n",htoi(str));
	}
	free(str);
	return 0;
}

long htoi(char *str){
	while(*str==' '){
		str++;
	}
	if(*str=='0'){
		str++;
		if(*str=='X'||*str=='x'){
			str++;
			long result=0;
			char c;
			while((c=*str)!='\0'){
				if(c>='0'&&c<='9'){
					result=result*16+c-'0';
				}
				else if((c=tolower(c))>='a'&&c<='f'){
					result=result*16+c-'a'+10;
				}
				else{
					break;
				}
				str++;
			}
			return result;
		}
	}
	fprintf(stderr,"not a hexadecimal!\n");
	exit(1);
}

