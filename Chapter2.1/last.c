#include <stdio.h>
#include <sys/types.h>
#include <utmp.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <pwd.h>


// /var/run/utmp
// /var/log/wtmp

void show_info(struct utmp* utbufp);
void showtime(long timeval);

int main(int argc, char **argv)

{
  struct utmp current_record;
  int fd;

  // open file
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
  
  //start reading
  
  int reclen = sizeof(current_record);
  
  while (read (fd, &current_record,reclen) == reclen)
    show_info(&current_record);
  close(fd);
  return 0;
}

void show_info(struct utmp* utbufp){
  //decode
  // printf("%2d", utbufp->ut_type);
  // printf(" ");
  
  // printf("%4d", utbufp->ut_pid);
  //printf(" ");

  
  printf("%-3.3s", utbufp->ut_id); //terminal suffix
  printf(" ");
  
  //printf("%-3d %3d", utbufp->ut_exit.e_termination,utbufp->ut_exit.e_exit);
  //printf(" ");
  struct passwd * pwd = getpwuid(utbufp->ut_pid);
  if (pwd != NULL){
  char * name = pwd -> pw_name;
  printf("%-8.8s",name);
  }
  else {
    printf("%.*",8,'0');
  }
  

  
  printf("%-8.8s", utbufp->ut_name); 
  printf(" ");

  printf("%-8.8s", utbufp->ut_user); 
  printf(" ");


  printf("%-8.8s", utbufp->ut_line); //tty
  printf(" ");

  showtime(utbufp->ut_time);
  printf(" ");

  printf("\n");
}

void showtime(long timeval){
  char *cp;
  cp = ctime(&timeval);
  printf("%12.12s", cp + 4);
  
}

/*
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
*/
