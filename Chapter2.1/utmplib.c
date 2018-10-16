#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <utmp.h>

#define NRECS 16
#define NULLUT ((struct utmp*)NULL)
#define UTSIZE (sizeof(struct utmp))


static char utmpbuf[NRECS * UTSIZE];
static int num_recs;
static int cur_rec;
static int fd_utmp = -1;

int utmp_seek(int record_offset, int base){
  
  switch(base){
  case SEEK_SET:
    if( record_offset < 0 )
      return -1;
    if( lseek(fd_utmp, record_offset * UTSIZE, SEEK_SET) == -1 ){
      return -1;
    }
    cur_rec = num_recs = 0;
    break;
  case SEEK_CUR:
    if ( lseek(fd_utmp, record_offset * UTSIZE, SEEK_CUR) == -1 ){
      return -1;
    }
    cur_rec = num_recs = 0;
  
  case  SEEK_END:
    if ( record_offset > 0){
      return -1;
    }
    if (lseek(fd_utmp, record_offset * UTSIZE, SEEK_END) == -1 ){
      return -1;
    }
    cur_rec = num_recs = 0;
  default:
    break;
  }
}

utmp_open(char *filename){
  fd_utmp = open(filename, O_RDONLY);
  cur_rec = num_recs = 0;
  return fd_utmp;
}

struct utmp * utmp_next(){
  struct utmp *recp;
  if (fd_utmp == -1)
    return NULLUT;
  if (cur_rec == num_recs && utmp_reload() == 0)
    return NULLUT;
  recp = (struct utmp *) &utmpbuf[cur_rec * UTSIZE];
  cur_rec++;
  //if (recp -> ut_type ==  DEAD_PROCESS){
  //  return utmp_next;
  // }
  return recp;
}
int utmp_reload(){
  int amt_read;
  amt_read = read(fd_utmp, utmpbuf, NRECS * UTSIZE);
  num_recs = amt_read/UTSIZE;
  cur_rec = 0;
  return num_recs;
}
utmp_close(){
  if(fd_utmp != -1)
    close(fd_utmp);
}
// pos starts with zero
int utmp_write()
{
  
  size_t pos = cur_rec - 1;

  if(lseek(fd_utmp, -(num_recs - pos) * UTSIZE, SEEK_CUR))
    if(write(fd_utmp,  (struct utmp *) &utmpbuf[cur_rec * UTSIZE], UTSIZE) == UTSIZE)
      if(lseek(fd_utmp, (num_recs - pos - 1)* UTSIZE  , SEEK_CUR))
	return 0;
  return 1;
}
