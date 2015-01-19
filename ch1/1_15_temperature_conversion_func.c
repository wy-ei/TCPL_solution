/*
 * 1-15. Rewrite the temperature conversion program of Section 1.2 to use a function
 * for conversion.
 *
 * wy-ei  2015.1.17
*/

#include <stdio.h>

void temperatureConvert(){
	float celsius,fahr;
	int lower,upper,step;

	lower=0;
	upper=300;
	step=20;

	fahr=lower;
	printf("fahrenheit  centigrade\n");
	while(fahr<upper){
		celsius = (5.0/9.0)*(fahr-32.0);
		printf("   %3.0f      %6.1f\n",fahr,celsius);
		fahr = fahr + step;
	}
}
int main(){
	temperatureConvert();
	return 0;
}

