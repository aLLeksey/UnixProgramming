#include <stdio.h>
#include <sys/types.h>
#include <utmp.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define SHOWHOST

// /var/run/utmp
// /var/log/wtmp

void show_info(struct utmp* utbufp);
void showtime(long timeval);

int main(int argc, char **argv)

{
  struct utmp current_record;
  int fd;

  // open another file
  if (argc == 2){
    char *name = argv[1];
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
  // open utmp
  else{
    if ((fd = open(UTMP_FILE, O_RDONLY)) == -1){
      perror(UTMP_FILE);
      exit(1);
    }
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
  
}
