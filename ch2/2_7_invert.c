/*
 * 2-7. Write a function invert(x,p,n) that returns x with the n bits that begin at
 * position p inverted (i.e., 1 changed into 0 and vice versa), leaving the others unchanged.
 *
 * wy-ei 2015.1.22
*/

#include <stdio.h>

void invert(unsigned *,int,int);

int main(){
	unsigned x=0x5505;
	int p = 7;
	int n = 4;

	invert(&x,p,n);

	printf("%x\n",x);   // 55f5

	return 0;
}

void invert(unsigned *x,int p,int n){
	*x = *x^(~(~0<<n)<<(p-n+1));   // 0^x=x  1^x=~x;
}

