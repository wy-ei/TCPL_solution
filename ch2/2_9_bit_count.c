/*
 * 2-9. In a two's complement number system, x &= (x-1) deletes the rightmost 1-bit
 * in x . Explain why. Use this observation to write a faster version of bitcount .
 *
 * wy-ei 2015.1.22
*/

#include <stdio.h>

int bitcount(unsigned x){
	int i;
	for(i=0;x!=0;x&=x-1){
		i++;
	}
	return i;
}


int main(){
	int x=0xaaaa5555;
	int n=x+20;
	while(x<n){
		printf("%08x : %d\n",x,bitcount(x));
		x++;
	}
	return 0;

}
