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




void work(FILE *file,Convert con){
  char a[0xa];
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
//what to do if in on time many bytes(chars)????
/*
1
2
3
4
5
6
7
      0 31 0a 32 0a 33 0a 34 0a 35 0a 36 37 38 
     13
8
9
10
11
12
0a 0a 38 
     16 0a 39 0a 31 30 0a 31 31 31 32 
     26
*/
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
