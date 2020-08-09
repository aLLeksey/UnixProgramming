#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>

void do_ls(char *);
void do_stat(char *);
void show_file_info(char *, struct stat *);
char *uid_to_name(uid_t);
char *guid_to_name(gid_t);

main(int argc, char** argv){
	if(argc == 1)
		do_ls(".");
	else
    while(--argc){
      printf("%s:\n",*argv);
      do_ls(*argv);
    }
}

/* 
 * enumerates files in directory with name dirname
 */
void do_ls(char *dirname){
  DIR *dir_ptr;
  if((dir_ptr = opendir(dirname)) == NULL){
    fprintf(stderr,"ls1:cannot open %s\n", dirname);
  }
  else{
    while((direntp = readdir(dir_ptr)) !=NULL){
      do_stat(direntr -> d_name);
    }
    closedir(dir_ptr);
  }
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
 *  show info of 'filename' from stuct. *info_p
 */
void show_file_info(char *filename, struct stat *info_p){
  char *uid_to_name(), *ctime(), *gid_to_name(), *filemode();
  void mode_to_letters();
  char modestr[11];
  mode_to_letters(info->st_mode,modestr);
  printf("%s", modestr);
  printf("%4d", (int)info_p->st_nlink);
  printf("%-8s", uid_to_name(info_p->st_uid));
  printf("%-8s", gid_to_name(info_p->st_gid));
  printf("%8ld", (long)info_p->st_size);
  printf(".12s", 4+citime(&info_p->st_mtime));
  printf("%s\n", filename);
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
  strncpy(str,"---------",10); // with /0

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

  if((pw_ptr = getpwuid) == NULL){
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
  struct *getgrdid(), *grp_ptr;
  static char numstr[10];

  if((get_ptr = getgrid(gid)) == NULL){
    //?????
    snprintf(numstr,sizeof(numstr)/sizeof(numstr[0]),"% d", gid);
    return numstr;
  }
  else 
    return gpr_ptr->gr_name
}
