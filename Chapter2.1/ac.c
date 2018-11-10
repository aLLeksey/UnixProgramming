#include <stdio.h>
#include <sys/types.h>
#include <utmp.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

long  count(int fd,int *OK );
long count_time(int fd);


int main(int argc, char **argv)

{
  struct utmp current_record;
  int fd;
  
  char *name = "/var/log/wtmp";
  FILE *in;
  in = fopen(name,"r");
  if (!in){
    perror(name);
    exit(1);
  }
  fd = fileno(in);
  if (fd == -1){
    perror("fd");
  }

  long t = count_time(fd);
  int h = t / 3600;
  t =  t % 3600;
  int min = t / 60;
  t = t % 60;
  int sec = t;
  printf("h = %ld, m = %ld, s = %ld\n", h , min, sec);

}

long count_time(int fd){
  int OK = 0;
  long res = 0;
  do{
    res += count(fd, &OK);
  }while(OK != -1);
  return res;
}

long  count(int fd,int *OK ){

  struct utmp current={0};
  
  int reclen = sizeof(current);
  
  
  //find first == 0 => drop
  //find first !=0
  //find first == 0;
  //substract time;
  // enjoy))

  //0
  //x
  //0

  
  
  // 0
  while (1){
    int r = read (fd, &current,reclen);
    if (!r){
      *OK = -1;
      return 0;
    }
    if (current.ut_type != 0){
      break;
    }
  }
  // x
  // first != 0
  long t1 = current.ut_time;
  
  while (1){
    int r = read (fd, &current,reclen);
    if (!r){
      long t2 = (long int)time(NULL);
      *OK = -1;
      return t2 - t1;
    }
  // 0
    if (current.ut_type == 0){
      break;
    }
  }

  // X 0
  // |-^ => t = 0 - X
  long t2 = current.ut_time;
  // [t2;t1)
  return t2 - t1;
}
  

