/*
 * 5-11. Modify the program entab and detab (written as exercises in Chapter 1) to
 * accept a list of tab stops as arguments. Use the default tab settings if there are no arguments.
 *
 * wy-ei 2015.2.9
*/



#include <stdio.h>
#include <stdlib.h>
#define N 4

int main(int argc,char *argv[]){
	int c;
	int nb=0; //number of blank
	int nt=0; //number of tab
	int stops;
	if(argc!=1){
		stops = atoi(argv[1]);
	}else{
		stops=N;
	}
	while((c=getchar())!=EOF){
		if(c==' '){
			nb++;
			continue;
		}
		if(c=='\t'){
			nb+=stops;
			continue;
		}
		if(nb==0){
			putchar(c);
		}
		else{
			nt=nb/stops;
			nb=nb%stops;
			while(nt!=0){
				putchar('\t');
				nt--;
			}
			while(nb!=0){
				putchar(' ');
				nb--;
			}
			putchar(c);
		}
	}
	return 0;
}
			
