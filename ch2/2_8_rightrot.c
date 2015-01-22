/*
 * 2-8. Write a function rightrot(x,n) that returns the value of the integer x rotated
 * to the right by n positions.
 *
 * wy-ei 2015.1.22
 */

#include <stdio.h>

unsigned rightrot(int x, int n){	
	int size=sizeof(x)*8;
	unsigned y=(unsigned)x;
	return y>>n | y << (size-n);
}

int main(){
	int x, n;
	x = 0x70f0f0f1; /* 0111 0000 1111 0000 1111 0000 1111 0001 */
	n = 4;
	printf("%08x >>(rotated) %d = %08x\n",x,n,rightrot(x,n));
	x = 0x170f0f0f; /* 0001 0111 0000 1111 0000 1111 0000 1111 */
	n = 8;
	printf("%08x >>(rotated) %d = %08x\n",x,n,rightrot(x,n));
	return 0;
}
