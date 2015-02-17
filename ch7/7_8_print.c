/*
 * 7-8. Write a program to print a set of files, starting each new one on a new page,
 * with a title and a running page count for each file.
 *
 * wy-ei 2015.2.16
*/

#include <stdio.h>
#define MAXLEN 1000

const int rows = 46;   // less 1 than the rows of sceen

int main(int argc,char *argv[]){
	if(argc<2){
		fprintf(stderr,"Usage:%s file1 [file2 file3 ...]",argv[0]);
		return 1;
	}
	int page=0;
	int linenum=0;
	char line[MAXLEN];
	FILE *fp;
	while(--argc){
		if((fp=fopen(*++argv,"r"))==NULL){
			fprintf(stderr,"error:open file fail\n");
			return 1;
		}
		while(fgets(line,MAXLEN,fp)!=NULL){
			if(linenum%rows==0){
				if(page>0){
					int c;
					printf("type q to quit! or other key continue. ");
					c=getchar();
					if(c==EOF||c=='q'){
						return 0;
					}
				}
				page++;
				linenum++;
				printf("file: %s  page: %d\n",*argv,page);
			}
			linenum++;
			printf("%s",line);
		}
		int i;
		for(i=linenum%rows;i<rows;i++){
			putchar('\n');
		}
	}
	return 0;
}




