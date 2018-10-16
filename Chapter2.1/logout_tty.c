#include <fcntl.h>
#include <sys/types.h>
#include <utmp.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

/* logout-tty(char *line)
 * mark utmp of logout
 * 0 : OK 
 * 1 : error
 */
int  logout_tty(char *line){
  int fd;
  struct utmp *rec;
  int len = sizeof(struct utmp);
  int retval = -1;
  if ((fd = open(UTMP_FILE, O_RDWR)) == -1)
    return -1;
while(rec = utmp_next())
    if (strncmp(rec->ut_line, line, sizeof(rec->ut_line)) == 0){
      rec->ut_type = DEAD_PROCESS;
      if(time(rec->ut_time) != -1)
	if (utmp_write() != 0) // success
	    retval = 0; 
	break;
    }

  if (close(fd) == -1)
    retval = -1;
  return retval;
}
