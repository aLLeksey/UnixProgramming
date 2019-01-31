#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int print_lines(const char* FILE_NAME, int cnt);
int print_bytes(const char *FILE_NAME, int cnt);
int rev_print(FILE *f, int cnt);
void print_c(char c, int times);
void run(int first_file, int last_file,const char * argv[],int cnt, int type);

#define min(a,b) (((a)<(b))?(a):(b))


int main(int argc, char* argv[]){
  if(argc <= 1){
    return 0;
  }
  int oc;
  char *n_arg = 0;
  int type = 0;
  int q = 1;
  while((oc = getopt(argc,argv,"c:n:qv")) != -1){
    switch(oc){
    case 'c':
      n_arg=optarg;
      type = 1;
      break;
    case 'n':
      n_arg=optarg;
      type = 0;
      break;
    case 'q':
      q = 0;
      break;
    case 'v':
      q = 0;
    }
  }
  int k = 10;
  if(n_arg != 0){
    k = atoi(n_arg+1);
  }
  if(optind<argc){
    run(optind,argc,argv,k,type);
  }
  return 0;
}

int print_bytes(const char *FILE_NAME, int cnt){
  FILE *f = fopen(FILE_NAME,"r");
  if(f==0)return 0;
   fseek(f,0,SEEK_SET);
  if(cnt < 0){
    // cnt = -cnt;
    long long t = ftell(f); // start file
    fseek(f,cnt,SEEK_END);
    if (ftell(f) == t){// abs(cnt)>=filesize; end_file+cnt<=beg_file
      return 0;
    }
    cnt = ftell(f);
    fseek(f,0,SEEK_SET);
    printf("lala cnt = %d",cnt);
  }
  printf("==> %s <==\n",FILE_NAME);
  char a[1000];
  while(cnt!=0){
    int k = fread(a,sizeof(char),min(cnt,999),f);
    if(k <= 999){
      a[k] = 0;
    }
    else{
      a[999] = 0;
    }
    printf("%s",a);
    cnt-=k;
  }
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

void run(int first_file, int last_file,const char * argv[], int cnt, int type ){
  for(int i = first_file; i < last_file;i++){
    if(type==0){
      print_lines(argv[i],cnt);
      //print_c('#',80);
    }
    else{
      print_bytes(argv[i],cnt);
    }
  }
}


int* map_lines(FILE * f){
  // line_number -> file_location
  // TODO  hash
  
  // N = ??? //prime
  typedef struct my_list{
    int val;
    my_list next;
  }list;

  mylist* [N];//Mallock?
  
  
