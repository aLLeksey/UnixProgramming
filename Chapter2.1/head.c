//TODO -> look BUGS file



#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include <fcntl.h>
#include<getopt.h>

//#define DEBUG

int print_lines(const char* FILE_NAME, int cnt);
int print_bytes(const char *FILE_NAME, int cnt);
int rev_print(FILE *f, int cnt);
void print_c(char c, int times);
void run(int first_file, int last_file,const char * argv[],int cnt, int type );

int find_digit(const char * s, int n);

long long N_LINES = 0;

typedef struct my_list{
  long long key;
  long long val;
  struct my_list * next;
}list;


//TODO make parameters work
//TODO make hash work
//DONE

list* find(list *l, long long key);
void add_node(list* l,list *node);
void _put(long long key, long long  val);
long long _get(long long  key);
void init();
void delete();

void make_map(FILE* f);
//void make_map(char* file);
void end_map();
long long get(long long line_num);

#define min(a,b) (((a)<(b))?(a):(b))
//#define TEST

#ifdef TEST1
#define H_SIZE 11 // for testing // file_size bytes
#else
#define H_SIZE  1000003 //prime > 1E6;
#endif
 

int main(int argc, char* argv[]){
  //parse(argc,argv);
  
  //start
  init();
  
  parse_long(argc, argv); // ... < set N_LINES
  
  /*
  char  file_name [] = "head.c";
  //
  FILE *f = fopen(file_name,"r");
  make_map(f);
  print_bytes(file_name, -2);
  //print_lines(file_name,-100);
  */;
  
  return 0;
}
int is_digit(char c){
  if(c>='0' && c <= '9'){
    return 1;
  }
  return 0;
}
int find_digit(const char * s, int n){
  int i = 0;
  while(i < n && !is_digit(s[i]))
    i++;
  return i;
}
/*
void parse(int argc, char **argv){
  if(argc <= 1){
    return;
  }
  int oc;
  char *n_arg = 0;
  int type = 0;
  int q = 1;
  // TODO getoptlong
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
*/
void parse_long(int argc, char **argv){
  
  if(argc <= 1){
    return;
  }
  int oc;
  char *n_arg = 0;
  int type = 0;
  int q = 1;
  struct option longopts[]={
			    { "bytes",required_argument,NULL,'c' },
			    { "lines",required_argument,NULL,'n' },
			    { "quiet",no_argument,NULL,'q' },
			    { "verbose",no_argument,NULL,'v'}
  };
  while((oc = getopt_long(argc,argv,":c:n:qv",longopts,NULL)) != -1){
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
      break;
    default:
      printf("Oops Error");
    }
  }
  int cnt = 10;
  
  if(n_arg != 0){
    char *p = strchr(n_arg,'=');
    if(p != 0){
      cnt = atoi(p+1);
    }
    else{
      cnt = atoi(n_arg);
    }
  }
  
#ifdef DEBUG
  printf("n_arg = %s\n", n_arg);
  printf("parse_cnt = %d\n", cnt);
#endif
  if(optind<argc){
    run(optind,argc,argv,cnt,type);
  }
  
}
////////////////OUTPUT FUNCTIONS//////////////////////////
//bytes //// lines /////////////////////////////////////////

int print_bytes(const char *FILE_NAME, int cnt){
  FILE *f = fopen(FILE_NAME,"r");
  if(f==0)return 0;
  fseek(f,0,SEEK_SET); //begining
  if(cnt < 0){ // print everything without count last bytes
    // cnt = -cnt;
    long long t = ftell(f); // start file
    fseek(f,cnt,SEEK_END);
    if (ftell(f) == t){// abs(cnt)>=filesize; end_file+cnt<=beg_file
      return 0;
    }
    cnt = ftell(f);
    fseek(f,0,SEEK_SET); //begining
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
#ifdef DEBUG
  printf("l_count = %d\n",cnt);
#endif
  FILE *f = fopen(FILE_NAME,"r");
  if(f==0)return 0;
  printf("==> %s <==\n",FILE_NAME);
  if(cnt < 0){ //print everything without count last lines
    cnt = N_LINES + cnt;
    if (cnt <= 0){
      return;
    }
  }
  char a[1000];
  for(int i = 0; i < cnt; i++){
    fgets(a,1000,f); // read line
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
///////////////END OUTPUT FUNCTIONS////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////




//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// TODO TODO TODO working with porblems lalalala
//test + work
//check map
//check output
//???


void run(int first_file, int last_file,const char * argv[], int cnt, int type ){
#ifdef DEBUG
  printf("run_cnt = %d\n",cnt);
#endif
  for(int i = first_file; i < last_file;i++){

    //BEGINING work with file
    
    //char file[] ="head.c";
    //FILE *f =fopen(file,"r");
    FILE *f = fopen(argv[i],"r");
  
    if(!f){
      return;
    }
    // BEG'ining map allockate memory
    make_map(f);
    //make_map(file);
    
    if(type==0){
      print_lines(argv[i],cnt);
      //print_c('#',80);
    }
    else{
      print_bytes(argv[i],cnt);
    }
    // END'ing map free memory
    end_map();
  }
}
///////////////////////////////////////////////////////////////////////////
//////////Lines-mapping methods////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
int *map = 0;
int IS_HASH = 0;

void make_map(FILE *f){
  int fd = fileno(f);
  int status = fcntl(fd,F_GETFL);
  // OK Its kinda working
  if(status&O_WRONLY)
    return;
  map_lines(f);
}
/*
OK Working
void make_map(char * file){
  FILE *f = fopen(file,"r");
  if(!f){
    return;
  }
  map_lines(f);
 }*/
void end_map(){
   if(IS_HASH){
    delete();
  }
  else{
    if(map!=0){
      free(map);
    }
  }
}


void map_lines(FILE * f){
  // line_number -> file_location
  // TODO  hash
  fseek(f,0,SEEK_END);
  long long N  = ftell(f);
  fseek(f,0,SEEK_SET);
  if(N <= H_SIZE){// array, no HASH
    IS_HASH = 0;
    
    map = malloc(N*sizeof(long long));
    memset(map,0,(N*sizeof(long long)));
    
    int k = 0;
    int i;   
    while((i = next_line(f))!=-1){
      map[k] = i;
      k++;
    }
    N_LINES = k;
  }
  else{//HASH
    IS_HASH = 1;
    int k = 0;
    int i;
    while((i = next_line(f))!=-1){
      _put(k,i);
      k++;
    }
  }
}
int next_line(FILE* f){
  char c = 0;
  while(c != EOF && c!= '\n'){
    c = fgetc(f);
  }
  if(c == EOF){
    return -1;
  }
  if(c == '\n'){
    return ftell(f);
  }
    
}





long long get(long long line_num){
  if(IS_HASH){
    return _get(line_num);
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
void _put(long long key, long long  val){
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
long long _get(long long  key){
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
      free(t);
    }
  }
}

void init(){
  memset(HASH,0,H_SIZE*sizeof(HASH[0]));
  
}


 
  
