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
