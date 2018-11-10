#include <stdio.h>
#include <sys/types.h>
#include <utmp.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char **argv)

{
  struct utmp current_record;
  int fd;

  // open another file
  if (argc == 2){
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
  }


}

double count(int fd){

  struct utmp current;
  
  int reclen = sizeof(current);
  
  strict utmp prev = {0};

  //find firs !=0
  //find fiest == 0;
  //substract time;
  // enjoy))


  
  while (true){
    int r = read (fd, &current_record,reclen);
    if (!r){
      return 0;
    }
    if (curren->ut_type == 0){
      break;
    }
    memcpy(prev, current, reclen);
  }
  if (prev->ut_type == 0){
    return 0;
  }
  t1 = prev->ut_time;

  while (true){
    int r = read (fd, &current_record,reclen);
    if (!r){
      long t2 = (long int)time(NULL);
      return t2 - t1;
    }
    if (curren->ut_type != 0){
      break;
    }
    memcpy(prev, current, reclen);
  }
  
  while (read (fd, &current_record,reclen) == reclen){
    if (current_recoord->ut_type == 0);
    else  break;
  }
  long t2 = current_record->ut_time;
  
  close(fd);
  return 0;
  
double difftime (time_t end, time_t beginning);



  void show_info(struct utmp* utbufp){
  //decode
  printf("%2d", utbufp->ut_type);
  printf(" ");
  
  printf("%4d", utbufp->ut_pid);
  printf(" ");

  
  printf("-%3.3s", utbufp->ut_id);
  printf(" ");
  
  printf("-%3d %3d", utbufp->ut_exit.e_termination,
	 utbufp->ut_exit.e_exit);
  printf(" ");
  
  printf("-%8.8s", utbufp->ut_name);
  printf(" ");

  printf("-%8.8s", utbufp->ut_line);
  printf(" ");
utbufp->ut_tim
  showtime(utbufp->ut_time);
  printf(" ");

#ifdef SHOWHOST
  printf("%s", utbufp -> ut_host);
#endif
  printf("\n");
}

void showtime(long timeval){
  char *cp;
  cp = ctime(&timeval);
  printf("%12.12s", cp + 4);

