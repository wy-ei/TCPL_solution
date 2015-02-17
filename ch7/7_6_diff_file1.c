/*
 * 7-6. Write a program to compare two files, printing the first line where they differ.
 *
 * wy-ei 2015.2.15
*/

#include <stdio.h>

#define MAXLEN 1001
int main(int argc,char *argv[]){
	char *prog=argv[0];
	if(argc!=3){
		fprintf(stderr,"Usage:%s file1 file2\n",prog);
		return 1;
	}
	char *file1,*file2;
	file1=argv[1],file2=argv[2];
	FILE *fp1,*fp2;
	if((fp1=fopen(file1,"r"))==NULL){
		fprintf(stderr,"open %s fail,pleasr check is this file exist.\n",file1);
		return 1;
	}
	if((fp2=fopen(file2,"r"))==NULL){
		fprintf(stderr,"open %s fail,pleasr check is this file exist.\n",file2);
		return 1;
	}
	
	char line1[MAXLEN],line2[MAXLEN];
	int linenum=0;
	while(fgets(line1,MAXLEN,fp1)!=NULL&&fgets(line2,MAXLEN,fp2)!=NULL){
		linenum++;
		if(strcmp(line1,line2)!=0){
			printf("diff at line %d:\nfile1:%s\nfile2:%s\n",linenum,line1,line2);
			break;
		}
	}
	
	return 0;
}
