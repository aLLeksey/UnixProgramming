#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>
#include<unistd.h>

void do_stat(char *);
void do_ls(char *);

void ls_list(char *);
void ls_column(char *);

void show_file_info(char *, struct stat *);
char *uid_to_name(uid_t);
char *guid_to_name(gid_t);

void ls_file(char *);
void ls_dir(char *);
int is_dir(char *);

char *prog_name;

int print_all = 0;

void (*ls_type)(char *dir_name);

char **start;

// TODO DONE
// (at least looks like this)
int main(int argc, char ** argv){
  //optind == 1
  parse();

  if(optind == argc){ //no OTHER options, current dir
    printf("optind=%d, argc=%d\n",optind,argc);
    do_ls(".");
    return 0;
  }
  // else
  while(optind<argc){ 
    //printf("%s\n",argv[optind++]);
    do_ls(argv[optind++]);
  }
}


/*
 * parses command options
 */
// TODO DONE
void parse(int argc, char **argv){
  ls_type = ls_column;
  int opt;
  while((opt = getopt(argc,argv, "acl")) != -1){
    switch (opt){
      case 'a':
        print_all = 1;
        break;
      case 'c':
        ls_type=ls_column;
        break;
      case 'l':
        ls_type=ls_list;
        break;
    }
  }
}
        
void do_ls(char *name){
  if(is_dir(name)){
    ls_dir(name);
  }else{
    ls_file(name);
  }
}

void ls_dir(char *name){
  ls_type(name);
}

void ls_file(char *name){
  if(ls_type==ls_list){
    do_stat(name);
  }
  else{
    // TODO
  }
}

  



// TODO test
/*
 * checks  if file  is directory or not
 */
int is_dir(char *name){
  struct stat path_stat;
  if(stat(name, &path_stat)!=0){
    return 0;
  }
  return S_ISDIR(path_stat.st_mode);
}








/* 
 * enumerates files in directory with name dirname
 */
void ls_list(char *dir_name){
  DIR *dir_ptr;
  struct dirent *direntptr;
  if((dir_ptr = opendir(dir_name)) == NULL){
    fprintf(stderr,"%s:cannot open %s\n",prog_name, dir_name);
  }
  else{
    while((direntptr = readdir(dir_ptr)) !=NULL){
      do_stat(direntptr -> d_name);
    }
    closedir(dir_ptr);
  }
}

void ls_column(char *dira_name){
}

void do_stat(char *filename){
  struct stat info;
  if (stat(filename, &info) == -1){
    perror(filename);
  }
  else{
    show_file_info(filename,&info);
  }
}

/*
 *  show info of 'filename' from stuct *info_p
 */
void show_file_info(char *filename, struct stat *info_p){
  char *uid_to_name(), *ctime(), *gid_to_name(), *filemode();
  void mode_to_letters();
  char modestr[11];
  mode_to_letters(info_p->st_mode,modestr);
  printf("%s", modestr);
  printf("%4d ", (int)info_p->st_nlink);
  printf("%-8s", uid_to_name(info_p->st_uid));
  printf("%-8s", gid_to_name(info_p->st_gid));
  printf("%8ld ", (long)info_p->st_size);
  printf("%.12s", 4+ctime(&info_p->st_mtime));
  printf(" %s\n", filename);
}

/*
 * utility functions
 */


/*
 * Take value of mode and forming array of chars
 * In char array put file type and 9 chars for acess rights.
 * WITHOUT setuid setgid sticky
 */
void mode_to_letters(int mode, char *str){
  strncpy(str,"----------",11); // with /0

/// TODO
// search how to write better!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  if (S_ISDIR(mode))str[0] = 'd';
  if (S_ISCHR(mode))str[0] = 'c';
  if (S_ISBLK(mode))str[0] = 'b';

  if (mode & S_IRUSR) str[1] = 'r';
  if (mode & S_IWUSR) str[2] = 'w';
  if (mode & S_IXUSR) str[3] = 'x';

  if (mode & S_IRGRP) str[4] = 'r';
  if (mode & S_IWGRP) str[5] = 'w';
  if (mode & S_IXGRP) str[6] = 'x';

  if (mode & S_IROTH) str[7] = 'r';
  if (mode & S_IWOTH) str[8] = 'w';
  if (mode & S_IXOTH) str[9] = 'x'; 

}

#include <pwd.h>

/*
 * return pointer to user_name according to uid. used by gtpw()
 */
char *uid_to_name(uid_t uid){
  struct passwd *getpwuid(), *pw_ptr;
  static char numstr[10];

  if((pw_ptr = getpwuid(uid)) == NULL){
    sprintf(numstr,"% d", uid);
    return numstr;
  }
  else{
    return pw_ptr->pw_name;
  }
}

#include <grp.h>

/*
 * return pointer to grpup_name. using getgrgid(3)
 */
char *gid_to_name(gid_t gid){
  struct group *getgrgid(), *grp_ptr;
  static char numstr[10];

  if((grp_ptr = getgrgid(gid)) == NULL){   //?????
    snprintf(numstr,sizeof(numstr)/sizeof(numstr[0]),"% d", gid);
    return numstr;
  }
  else
    return grp_ptr->gr_name;
}
