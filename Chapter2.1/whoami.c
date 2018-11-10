#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

int main(){

  size_t euid = geteuid();
  struct passwd * pwd = getpwuid(euid);
  char * name = pwd -> pw_name;
  printf("%s\n",name);
  return 0;
}
