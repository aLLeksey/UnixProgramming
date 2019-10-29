#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

#define DEBUG


typedef (*Convert)(char **, char);

int open_file(char *file_name);
void parse();
void work(FILE *file,Convert con);
int  process(char *str, Convert con, int len);


void to_oct(char **sp, char c);
void to_hex(char **sp, char c);



int main(){
  work(stdin,to_hex);
  return 0;
}



void work(FILE *file,Convert con){
  char a[0x11];
  a[0x10] = 0;
  while(1){
  int i = 0;
    while(i < 0x10){
      char c = fgetc(file);
      if(c == EOF){
	int k = process(a,con,i);
	printf("%07o\n",k);
	return;
      }
      a[i] = c;
      i++;
    }
    process(a,con,i);
  }
}

int  process(char *str, Convert con, int len){
  static int i = 0;
  printf("%07o ",i);
  int j = 0;
  while(j <= 0x10 && j < len && str[j] != 0){
    char c = str[j];
    char *s = NULL;
    con(&s,c);
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

  return  i;
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
