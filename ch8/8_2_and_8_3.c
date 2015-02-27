/*
 * 8-2. Rewrite fopen and _fillbuf with fields instead of explicit bit operations.
 * Compare code size and execution speed.
 *
 * wy-ei 2015.2.20
 */



#include <stdlib.h>

#undef  NULL
#define NULL     0
#define EOF      (-1)
#define BUFSIZ   1024
#define OPEN_MAX 20

typedef struct _iobuf{
	int cnt;		//character left
	char *ptr;		//next character position
	char *base;		//location of buffer
	int  flag;	    //mode of file access
	int fd;			//file description
}FILE;



 FILE _iob[OPEN_MAX];

#define stdin   (&_iob[0])
#define stdout  (&_iob[1])
#define stderr  (&_iob[2])

enum _flags{
	_READ = 01,
	_WRITE =02,
	_UNBUF = 04,
	_EOF = 010,
	_ERR = 020,

};


FILE _iob[OPEN_MAX]={
	{0,(char *)0,(char *)0,_READ,0},
	{0,(char *)0,(char *)0,_WRITE,1},
	{0,(char *)0,(char *)0,_WRITE|_UNBUF,2}
};

int _fillbuf(FILE *fp){
	int bufsize;

	if(fp->flag&(_READ|_EOF|_ERR)!=_READ)
	  return EOF;
	bufsize=(fp->flag&_UNBUF)?1:BUFSIZ;

	if(fp->base==NULL){
		if((fp->base=(char *)malloc(bufsize))==NULL){
			return EOF;
		}
	}
	fp->ptr=fp->base;
	fp->cnt=read(fp->fd,fp->ptr,bufsize);
	if(--fp->cnt<0){
		if(fp->cnt==-1){
			fp->flag|=_EOF;
		}else{
			fp->flag|=_ERR;
		}
		fp->cnt=0;
		return EOF;
	}
	return (unsigned char)*fp->ptr++;
}

int _flushbuf(int c,FILE *fp){


	int bufsize,num_writen;
	unsigned char uc = c;

	if(fp<_iob||fp>_iob+OPEN_MAX){
		return EOF;
	}

	if(fp->flag&(_WRITE|_EOF|_ERR)!=_WRITE){
		return EOF;
	}

	if(fp->base==NULL&&((fp->flag&_UNBUF)==0)){
		//no buffer yet
		if((fp->base=malloc(BUFSIZ))==NULL){
			//couldn't allocate a buffer,try unbuffered
			fp->flag|=_UNBUF;
		}else{
			fp->ptr=fp->base;
			fp->cnt=BUFSIZ-1;
		}
	}
	if(fp->flag&_UNBUF){
		//unbuffered write
		fp->ptr=fp->base=NULL;
		fp->cnt=0;
		if(c==EOF){
			return EOF;
		}
		num_writen=write(fp->fd,&uc,1);
		bufsize=1;
	}else{
		//buffered write
		if(c!=EOF){
			*fp->ptr++=uc;
		}
		bufsize=(int)(fp->ptr-fp->base);
		num_writen=write(fp->fd,fp->base,bufsize);
		fp->ptr=fp->base;
		fp->cnt=BUFSIZ-1;
	}
	if(num_writen==bufsize){
		return c;
	}else{
		fp->flag|=_ERR;
		return EOF;
	}
}

#define feof(p)    (((p)->flag & _EOF)!=0)
#define ferror(p)  (((p)->flag & _ERR)!=0)
#define fileno(p)  ((p)->fd)

#define getc(p)	   (--(p)->cnt>=0?(unsigned char)*(p)->ptr++:_fillbuf(p))
#define putc(x,p)  (--(p)->cnt>=0?*(p)->ptr++=(x):_flushbuf((x),p))

#define getchar()  getc(stdin)
#define putchar(x) putc(x,stdout);

#include <fcntl.h>
#include <sys/syscall.h>
#define PERMS 0666


FILE *fopen(char *name,char *mode){
	int fd;  
	FILE *fp;
	if(*mode!='w'&&*mode!='r'&&*mode!='a'){
		return NULL;
	}
	for(fp=_iob;fp<_iob+OPEN_MAX;++fp){
		if((fp->flag&(_READ|fp->flag))==0)
		  break;  //found free slots
	}
	if(fp>=_iob+OPEN_MAX){
		return NULL;
	}
	if(*mode=='w'){
		fd=creat(name,PERMS);
	}else if(*mode=='a'){
		if((fd=open(name,O_WRONLY,0))==-1){
			fd=creat(name,PERMS);
		}
		lseek(fd,0L,2);
	}else{
		fd=open(name,O_RDONLY,0);
	}
	if(fd==-1){
		return NULL;
	}
	fp->fd=fd;
	fp->cnt=0;
	fp->base=NULL;
	fp->flag=(*mode=='r')?_READ:_WRITE;
	return fp;
}

int fflush(FILE *fp){
	int retval;
	int i;
	if(fp==NULL){
		//flush all output streams
		for(i=0;i<OPEN_MAX;i++){
			if(((_iob+i)->flag&_WRITE)&&(fflush(_iob+i)==-1)){
				retval=-1;
			}
		}
	}else{
		if((fp->flag&_WRITE)==0){   //not output stream
			return -1;
		}
		_flushbuf(EOF,fp);
		if(fp->flag&_ERR){
			retval=-1;
		}
	}

	return retval;
}

int fclose(FILE *fp){
	int fd;

	if(fp==NULL){
		return -1;
	}
	fd=fp->fd;
	fflush(fp);
	fp->cnt=0;
	fp->ptr=NULL;
	if(fp->base!=NULL){
		free(fp->base);
		fp->base=NULL;
	}
	fp->flag=0;
	fp->fd=-1;

	return close(fd);
}
int main(){
	FILE *fp = fopen("test.txt","r");

	int c;
	while((c=getc(fp))!=EOF){
		putchar(c);
	}

	fclose(fp);
	
	return 0;
}
