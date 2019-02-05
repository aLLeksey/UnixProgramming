#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
int print_lines(const char* FILE_NAME, int cnt);
int print_bytes(const char *FILE_NAME, int cnt);
int rev_print(FILE *f, int cnt);
void print_c(char c, int times);
void run(int first_file, int last_file,const char * argv[],int cnt, int type );


int IS_HASH = 0;



typedef struct my_list{
  long long key;
  long long val;
  struct my_list * next;
}list;



list* find(list *l, long long key);
void add_node(list* l,list *node);
void put(long long key, long long  val);
long long get(long long  key);
void init();
void delete();

#define min(a,b) (((a)<(b))?(a):(b))
//#define TEST

#ifdef TEST
#define H_SIZE 11 // for testing
#else
#define H_SIZE  1000003 //prime > 1E6;
#endif
 

int main(int argc, char* argv[]){
  //parse(argc,argv);
  init();
  
  delete();
  return 0;
}

void parse(int argc, char **argv){
  if(argc <= 1){
    return;
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

int *map = 0;

int* map_lines(FILE * f){
  // line_number -> file_location
  // TODO  hash
  fseek(f,0,SEEK_END);
  long long N = ftell(f);
  if(N <= 1E6){// array, no HASH
    IS_HASH = 0;
    map = malloc(N*sizeof(long));
    //malloc
    
  }
  else{//HASH
    IS_HASH = 1;
  }
}

long long in_file(long long line_num){
  if(IS_HASH){
    return get(line_num);
  }
  else{
    return map[line_num];
  }
}
  





//////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
// Work with HASH functions
/////////////////////////////////////////////////////////////////////
/*
typedef struct my_list{
  long long key;
  long long val;
  struct my_list * next;
}list;
*/

list* HASH[H_SIZE];

void make_hash(){ // N prime > 1E6
}
void put(long long key, long long  val){
  long long k = key % H_SIZE;
  list * l = malloc(sizeof(list));
  memset(l,0,sizeof(list));
  l->key = key;
  l->val = val;
  l->next = NULL;
  if(HASH[k] == 0){
    HASH[k] = l;
  }
  else{
    add_node(HASH[k],l);
  }
}
long long get(long long  key){
  long long k = key % H_SIZE;
  list *l = find(HASH[k],key);
  if(HASH[k] != 0){
  }
  if(l == NULL){
    return -1;
  }
  return l->val;
  
}

list* find(list *l, long long key){
  while(l!=NULL){
    if(key == l->key){
       return l;
    }
    l=l->next;
  }
  return NULL;
}

void add_node(list* l,list *node){
  while(l->next != NULL){
    l = l->next;
  }
  l->next=node;
}
 
void delete(){
  for(int i = 0; i < H_SIZE;i++){
    list*l = HASH[i];
    while(l != NULL){
      list*t=l;
      l=l->next;
      free(l);
    }
  }
}

void init(){
  memset(HASH,0,H_SIZE*sizeof(HASH[0]));
}


 
  
