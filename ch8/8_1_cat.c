/*
 * 8-1. Rewrite the program cat from Chapter 7 using read , write , open , and close
 * instead of their standard library equivalents. Perform experiments to determine the relative
 * speeds of the two versions.
 *
 * wy-ei 2015.2.20
*/


#include <stdio.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <stdlib.h>

main(int argc,char *argv[]){
	int f1,f2,n;
	char buf[BUFSIZ];

	if(argc<2){
		fprintf(stderr,"Usage:cat file [file2 ...]\n");
		exit(1);
	}
	while(--argc){
		++argv;
		if((f1=open(*argv,O_RDONLY,0))==-1){
			fprintf(stderr,"error:can't open file %s",*argv);
		}
		while((n=read(f1,buf,BUFSIZ))>0){
			write(1,buf,n);
		}
		close(f1);
	}

	return 0;
}
