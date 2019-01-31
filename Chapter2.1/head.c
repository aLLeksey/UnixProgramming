#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int print_lines(const char* FILE_NAME, int cnt);
int print_bytes(const char *FILE_NAME, int cnt);
int rev_print(FILE *f, int cnt);
void print_c(char c, int times);
void run(int first_file, int last_file,const char * argv[],int bytes);

#define min(a,b) (((a)<(b))?(a):(b))

int main(int argc, char* argv[]){
  if(argc <= 1){
    return 0;
  }
  int oc;
  char *bytes_arg = 0;
  char *lines_arg = 0;
  int q = 1;
  while((oc = getopt(argc,argv,"c:nqv")) != -1){
    switch(oc){
    case 'c':
      bytes_arg=optarg;
      printf("!!!%s!!!",optarg);
      break;
    case 'n':
      lines_arg=optarg;
      break;
    case 'q':
      q = 0;
      break;
    case 'v':
      q = 0;
    }
  }
  int k_bytes = 0;
  if(bytes_arg != 0){
    k_bytes = atoi(bytes_arg+1);
    printf("\n%d\n",k_bytes);
  }
  if(optind<argc){
    run(optind,argc,argv,k_bytes);
  }
  return 0;
}

int print_bytes(const char *FILE_NAME, int cnt){
  FILE *f = fopen(FILE_NAME,"r");
  if(f==0)return 0;
  if(cnt < 0){
    fseek(f,-cnt,SEEK_END);
  }
  printf("==> %s <==\n",FILE_NAME);
  char a[1000];
  printf("321 %d\n",cnt);
  int k = 0;
  while(k<min(cnt,999)){
    k+=fread(a+k,min(cnt,999),sizeof(char),f);
  }
  printf("123\n%d\n",k);
  if(k <= 999){
    a[k] = 0;
  }
  else{
    a[999] = 0;
  }
  printf("%s",a);
  printf("\n");
}
  

int print_lines(const char* FILE_NAME, int cnt){
  FILE *f = fopen(FILE_NAME,"r");
  if(f==0)return 0;
  printf("==> %s <==\n",FILE_NAME);
  char a[1000];
  for(int i = 0; i < cnt; i++){
    fgets(a,1000,f);
    printf("%s",a);
  }
  printf("\n");
}
void print_c(char c, int times){
  int i = 0;
  while(i<times){
    putchar(c);
    i++;
  }
}	

void run(int first_file, int last_file,const char * argv[], int bytes ){
  for(int i = first_file; i < last_file;i++){
    if(bytes==0){
      print_lines(argv[i],10);
      //print_c('#',80);
    }
    else{
      print_bytes(argv[i],bytes);
    }
  }
}


