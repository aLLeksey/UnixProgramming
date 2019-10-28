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

// array of structures of string ??? how save in memory ???
// save chars and then in moment all 8????

void work(FILE *file,Convert con){
  char c;
  int i = 0;
  while((c = fgetc(file)) != EOF){
    char *s = NULL;
    con(&s,c);
    if(i % 16 == 0){
      printf("%7d ",i);
    }
    printf("%s ",s);
    free(s);
    i++;
    if(i%16 == 0){ // i != 0
      printf("\n");
    }
  }
  if(i%16!=0){
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
