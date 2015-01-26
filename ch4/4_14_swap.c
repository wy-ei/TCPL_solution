/*
 * 4-14. Define a macro swap(t,x,y) that interchanges two arguments of type t .
 * (Block structure will help.)
 *
 * wy-ei 2014.1.24
*/


#include <stdio.h>

#define swap(t,x,y)   t tmp;\
				      tmp=x;x=y;y=tmp;
int main(){

	double a=111.1;
	double b=999.9;
	printf("a:%f  b:%f\n",a,b);
	
	swap(int,a,b);

	printf("after swap:\na:%f  b:%f\n",a,b);

	return 0;
}
