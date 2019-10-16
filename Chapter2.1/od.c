#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

#define DEBUG

int open_file(char *file_name);
void parse();
void work(FILE *file);


void to_oct(char **sp, char c);
void to_hex(char **sp, char c);

typedef (*Convert)(char **, char);


int main(){
  work(stdin);
  return 0;
}

void work(FILE *file){
  char c;
  while((c = fgetc(file)) != EOF){
    char *s = NULL;
    // Not working
    //to_hex(&s,c);
    Convert con = to_hex;
    con(&s,c);
    printf("%s\n",s);
    printf("%02x\n",c);
#ifdef DEBUG
    printf("la\n");
    printf("c=%c\n",c);
#endif
    free(s);
  }
  
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
