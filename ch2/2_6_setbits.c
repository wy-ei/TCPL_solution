/*
 * 2-6. Write a function setbits(x,p,n,y) that returns x with the n bits that begin at
 * position p set to the rightmost n bits of y , leaving the other bits unchanged.
 *
 * wy-ei 2015.1.22
*/

#include <stdio.h>

void setbits(unsigned x,int p,int n,unsigned *y);

int main(){
	unsigned x,y;
	int p,n;

	x=0xaaaa;
	y=0xffff;

	p=7;    //position is begin at 0 , 0,1,2,3,4,...
	n=4;		

	setbits(x,p,n,&y);

	printf("%x\n",y);

	return 0;
}


void setbits(unsigned x,int p,int n,unsigned *y){
	*y = (*y&(~0<<n))|(x>>(p-n+1));   // *y&(~0<<n)  : set rightmost n bits to 0
									  // x>>(p-n+1)  : right shift the desired field to the right end of the word
									  // and than do | operation
}						
										      
