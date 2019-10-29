#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

#define DEBUG


typedef (*Convert)(char **, char);

int open_file(char *file_name);
void parse();
void work(FILE *file,Convert con);


void to_oct(char **sp, char c);
void to_hex(char **sp, char c);



int main(){
  work(stdin,to_hex);
  return 0;
}
/*
1234567890abcdefgh
      0 31 32 33 34 35 36 37 38 39 30 61 62 63 64 65 66 
     16
*/



void work(FILE *file,Convert con){
  char a[0x11];
  a[0x10] = 0;
  while(1){
  int i = 0;
    while(i < 0x10){
      char c = fgetc(file);
      if(c == EOF){
	process(a,con,i);
	return;
      }
      a[i] = c;
      i++;
    }
    process(a,con,i);
  }
}

void process(char *s, Convert con, int len){
  static int i = 0;
  int j = 0;
  while(j <= 0x10 && j < len && s[j] != 0){
    char c = s[j];
    char *s = NULL;
    con(&s,c);
    if(i % 0x10 == 0){
      printf("%7d ",i);
    }
    printf("%s ",s);
    free(s);
    i++;
    if(i%0x10 == 0){
      printf("\n");
    }
    j++;
  }
  if(i%0x10 != 0){
    printf("\n");
  }
  printf("%7d",i);
}

int open_file(char *file_name){
  
  // fomm FiLE* to int
  // fileno(f)

  //open
  FILE *f = fopen(file_name,"r");
  return fileno(f);
}

void parse(){
  // if file_name == '-' => no file
}


void to_oct(char **sp, char c){
  *sp = malloc(sizeof(char) * 3);
  snprintf(*sp,3,"%03o",c);
   
}

void to_hex(char **sp, char c){
  *sp = malloc(sizeof(char) * 3);
  snprintf(*sp,3,"%02x",c);
}
