#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int open_file(char *file_name);
void parse();
void work(FILE *file);

void to_bin(char **sp, char c);
void to_oct(char **sp, char c);
void to_hex(char **sp, char c);



int main(){
  work(stdin);
  return 0;
}

void work(FILE *file){
  char c;
  while((c = fgetc(file)) != EOF){
    char *s = NULL;
    to_hex(&s,c);
    printf("%s\t",s);
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

void to_bin(char **sp, char c){
  *sp = malloc(sizeof(char) * sizeof(char));
  //itoa(c,*sp,2);
  // TODO
  // write custom converter 2 b
}

void to_oct(char **sp, char c){
  *sp = malloc(sizeof(char) * 3);
  snprintf(*sp,3,"%03o");
   
}

void to_hex(char **sp, char c){
  *sp = malloc(sizeof(char) * 2);
  snprintf(*sp,2,"02x");
}
