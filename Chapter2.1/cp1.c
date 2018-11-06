#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define BUFFERSIZE 4096
#define COPYMODE 0644

void oops(char *,char *);
int main(int ac, char *av[]){
  int in_fd, out_fd, n_chars;
  char buf[BUFFERSIZE];
  /*if (ac != 3){
    fprintf(stderr, "usage: %s source detination \n", * av);
    exit(1);
    }*/
  if((in_fd = open(av[1], O_RDONLY)) == -1)
    oops("Cannt open", av[1]);

  if (ac == 4 && strncmp(av[3],"-i",2) == 0){
    printf ("A u shure?(y/n)\n");
    char c = getchar();
    if (c == 'n')
      exit(0);
  }
  
  if ((out_fd = creat(av[2], COPYMODE)) == -1)
      oops("Cannot create", av[2]);
  //copy

  while((n_chars = read(in_fd, buf, BUFFERSIZE)) > 0){
    if(n_chars == -1)
      oops("read error from", av[1]);
    if(write(out_fd, buf, n_chars) != n_chars)
      oops("write error to ", av[2]);
  }
  if(close(in_fd) == -1|| close(out_fd) == -1)
    oops("error closing files", "");
}
void oops(char *s1, char *s2){
  fprintf(stderr, "Error: %s ",s1);
  perror(s2);
  exit(1);
}
