/*
 * 8-4. The standard library function
 * int fseek(FILE *fp, long offset, int origin)
 * is identical to lseek except that fp is a file pointer instead of a file descriptor and return value
 * is an int status, not a position. Write fseek . Make sure that your fseek coordinates properly
 * with the buffering done for the other functions of the library.
 *
 * wy-ei 2015.2.27
*/


#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

int fseek(FILE *f, long offset, int whence) {
    int result;

    if((fp->flag & _UNBUF) == 0 && fp->base != NULL) {
        //deal with buffering
        if(fp->flag & _WRITE) {
            //writing,so flush buffer
            if(fflush(fp)) {
                return EOF;
            }
        } else if(fp->flag & _READ) {
            if(whence == SEEK_CUR) {
                if(offset >= 0 && offset <= f->cnt) {
                    fp->cnt -= offset;
                    fp->ptr += offset;
                    fp->flag &= ~_EOF; //clear EOF flag
                    return 0;
                } else {
                    offset -= f->cnt;
                }

            }
            fp->cnt = 0;
            fp->ptr = fp->base;
        }
    }
    result = (lseek(fp->fd, offset, whence) < 0);
    if(result == 0) {
        fp->flag &= ~_EOF; //if successful,clear EOF flag
    }
    return reult;
}
