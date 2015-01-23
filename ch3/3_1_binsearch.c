/*
 * 3-1. Our binary search makes two tests inside the loop, when one would suffice (at
 * the price of more tests outside.) Write a version with only one test inside the loop and
 * measure the difference in run-time.
 *
 * wy-ei 2015.1.22
 */

#include <stdio.h>
#include <stdlib.h>

int binsearch(int x,int *v,int n);

#define LEN(x) (sizeof(x)/sizeof(x[0]))

int main(){
	int a[]={4,12,32,65,87,90,103,112,114,123,156};
	int pos;
	pos = binsearch(32,a,LEN(a));
	if(pos==-1){
		printf("never finded\n");
	}else{
		printf("position:%d\n",pos);
	}

	return EXIT_SUCCESS;
}

int binsearch(int x,int *v,int n){
	int low,high,mid;
	low = 0;
	high = n-1;

	while(low<high){
		mid = (high+low)/2;
		if(v[mid]>=x){
			high = mid;
		}else{
			low = mid+1;
		}
	}
	return (v[low]==x)?low:-1;
}
	

