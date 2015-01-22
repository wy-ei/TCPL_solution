/*
 * 2-1. Write a program to determine the ranges of char , short , int , and long
 * variables, both signed and unsigned , by printing appropriate values from standard headers
 * and by direct computation. Harder if you compute them: determine the ranges of the various
 * floating-point types.
 *
 * wy-ei 2015.1.21
 *
*/

#include <stdio.h>
#include <float.h>
#include <limits.h>

#define MIN(x)  (-(x>>1)-1)
#define MAX(x)	(x>>1)
#define UMAX(x) x

int main(){
	printf("char Max:%d  char Min:%d\n",CHAR_MAX,CHAR_MIN);
	printf("unsigned char Max:%u unsignd char Min:%u\n",UCHAR_MAX,0);
	printf("short Max:%d  short Min:%d\n",SHRT_MAX,SHRT_MIN);
	printf("unsigned short Max:%u  unsigned short Min:%u\n",USHRT_MAX,0);
	printf("int Max:%d  int Min:%d\n",INT_MAX,INT_MIN);
	printf("unsigned int Max:%u  unsigned int Min:%u\n",UINT_MAX,0);
	printf("long Max:%ld  long Min:%ld\n",LONG_MAX,LONG_MIN);
	printf("unsigned long Max:%lu  unsigned long Min:%u\n",ULONG_MAX,0);

	unsigned char  c = ~0;
	unsigned int   i = ~0;
	unsigned short s = ~0;
	unsigned long  l = ~0;
	
	printf("----\n");
	printf("char Max:%d  char Min:%d\n",MAX(c),MIN(c));
	printf("unsigned char Max:%u unsignd char Min:%u\n",UMAX(c),0);
	printf("short Max:%d  short Min:%d\n",MAX(s),MIN(s));
	printf("unsigned short Max:%u  unsigned short Min:%u\n",UMAX(s),0);
	printf("int Max:%d  int Min:%d\n",MAX(i),MIN(i));
	printf("unsigned int Max:%u  unsigned int Min:%u\n",UMAX(i),0);      // u 
	printf("long Max:%ld  long Min:%ld\n",MAX(l),MIN(l));				  // ld
	printf("unsigned long Max:%lu  unsigned long Min:%u\n",UMAX(l),0);   // lu

	return 0;
}
