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
// /var/log/btmp

void show_info(struct utmp* utbufp);
void showtime(long timeval);

void print_time_end(long timeval);
void print_time_diff(long t1, long t2);

int main(int argc, char **argv)

{
  struct utmp current;
  struct utmp next;
  struct utmp *c,*n,*t;
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
  
  int reclen = sizeof(current);

  long prev = 0;
  c = &current;
  n = &next;

  if (read (fd,c,reclen)!= reclen){
    return 0;
  }  
  while (1){       
    show_info(c);
    if (read (fd,n,reclen) == reclen){
      print_time_end(n->ut_time);
      print_time_diff(c->ut_time, n->ut_time);
      t = c;
      c = n;
      n = t;  
    }
    else{
      printf("  still running");
      break;
    }
  }
  
  
  close(fd);


  
  return 0;
}

void show_info(struct utmp* utbufp){

  if( utbufp->ut_host == NULL || *utbufp->ut_host == '\0'){
    return;
  }
  
  
  
               printf("%-3.3s", utbufp->ut_id); //terminal suffix
  printf(" ");
  
  printf("%-3d", utbufp->ut_session);
  printf(" ");


  printf("%-8.8s", utbufp->ut_host);
  // print(utbufp -> ut_host);
  // printf("%p", utbufp->ut_host);
  printf(" ");
	
  
  printf("%-8.8s", utbufp->ut_name); 
  printf(" ");

  printf("%-8.8s", utbufp->ut_user); 
  printf(" ");


  printf("%-8.8s", utbufp->ut_line); //tty
  printf(" ");

  showtime(utbufp->ut_time);
  printf(" ");

  //printf("\n");
  
}

void showtime(long timeval){
  char *cp;
  cp = ctime(&timeval);
  printf("%16.16s", cp);
}

void print_time_end(long timeval){
  char *cp;
  cp = ctime(&timeval);
  printf(" - %5.5s", cp + 12);
}
void print_time_diff(long t1, long t2){
  long diff = t2 - t1;
  long h = diff / 3600;
  diff = diff % 3600;
  int min = diff / 60;
  printf("%2.2ld:%2.2d\n", h, min);
}
