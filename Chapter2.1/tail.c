//TODO -> BUGS

#define DEBUG
#define TEST

#include<stdio.h>
#include<string.h>
#include<getopt.h>
#include<stdlib.h>
#include<errno.h>

#ifdef TEST
#define BUF_SIZE 10
#else
#define BUF_SIZE 1000
#endif

#define N_LINES 10
#define min(x, y)  ((x) < (y) ? (x) : (y))
#define FNAME_SIZE 0xFFF

int PRINT_HEADERS = 1;
int IS_LINES = 0;


typedef struct fn{
  FILE *file;
  char *name;
  struct fn *next;
  long position;
}file_node;

file_node *HEAD = NULL;
file_node *TAIL = NULL;

int find_pos(long *n, char* buf);
long find_nline(FILE *f, long n_lines);
long find_nline_trunc(FILE *f);
void print_last_lines(FILE *f, long n);
void print_last_bytes(FILE *f, long n);
void print_pos(FILE* f, long pos);
void follow_file(int first_file, int last_file, char * argv[]);
void run(int first_file, int last_file,char *  argv[], long cnt);
int main(int argc, char *argv[]){

  parse_long(argc, argv);
  
}

long convert(char *arg){
  if(arg == 0){
    return -1;
  }
  errno = 0;
  long res = 0;
  char *endptr = NULL;
  char *nptr = NULL;
  char *p = strchr(arg,'=');
  if(p != 0){
    res =  strtol(p+1,&endptr,10);
    nptr = p+1;
  }
  else{
    res = strtol(arg,&endptr,10);
    nptr = arg;
  }
  if(errno!=0||endptr==nptr){
    return -1;
  }
  return res;
}


		 
// parcer
void parse_long(int argc, char* argv[]){
  int follow = 0;
  if(argc <= 1){
    return;
  }
  int is_lines = 0;
  int oc;
  char * _optarg = NULL;
  struct  option longopts[] = {
			       {"bytes",required_argument,NULL,'c'},
			       {"lines",required_argument,NULL,'n'},
			       {"follow",no_argument,NULL,'f'},
			       {"verbise",no_argument,NULL,'v'},
			       {"quit",no_argument,NULL,'q'},
			       {"help", no_argument,NULL,'h'}
  };

  
  while((oc = getopt_long(argc,argv,":c:n:fvqh",longopts,NULL)) != -1){
    switch(oc){
    case'c':   
      IS_LINES = 0;
      _optarg=optarg;
      break;
    case 'n':
      IS_LINES = 1;
      _optarg=optarg;
      break;
    case 'f':
      follow=1;
      break;
    case 'v':
      PRINT_HEADERS=1;
      break;
    case 'q':
      PRINT_HEADERS=0;
      break;
    default:
      printf("***OOps we are here***\n");
      return;
    }
  }
  long cnt = convert(_optarg);
  if( cnt == -1 ){
    cnt = N_LINES;
  }    
  // Print files according to opts
  if(optind<argc){
    if(follow){
      follow_file(optind,argc,argv);
    }
    else{
      run(optind,argc,argv,cnt);
    }
  }

}

		 
void run(int first_file, int last_file, char * argv[], long cnt){
  int is_lines = IS_LINES;
  
  for(int i = first_file; i < last_file; i++){
    long pos = 0;
    //BEGINING work with file;  
    FILE *f = fopen(argv[i],"r");  
    if(!f){
      continue;
    };    
    add(f,argv);
    print_headers(argv);
    print_last(f,cnt);
  }
}

void print_headers(char *s){
  if(PRINT_HEADERS){
    printf("===%s===\n",s);
  }
}

void print_last(FILE *f, long cnt){

  long pos = 0;
  if(IS_LINES){
    pos = find_nline(f,cnt); //TODO change to find_line // <-???
  }
  else{
    pos = -cnt;	
  }
  print_pos(f,pos);
}
		 
void follow_file(int first_file, int last_file, char * argv[]){
  
  run(first_file,last_file,argv,N_LINES);

  while(1){
    file_node *l = HEAD;
    while(l != 0 ){
      if(file_added(l->file)){
	print_headers(l->name);
	print_file(l->file);
      }
      l = l -> next;
    }
  }  
}

int file_added(FILE *f){
  long tell_cur = ftell(f);
  fseek(f,0,SEEK_END);
  long tell_end = ftell(f);

  if(tell_cur != tell_end){
    printf("%d %d\n",tell_cur,tell_end);
    if(tell_cur > tell_end){
      /*
      printf("file truncated");
      //if trunct stat -N_LINES from begining
      fseek(f,0,SEEK_SET);
      long pos = find_nline_trunc(f);
      fseek(f,pos,SEEK_SET);
      */
      //OR
      //if trunct. => start from begining
      fseek(f,0,SEEK_SET);
      return 0;
    }
    else{
      fseek(f,tell_cur,SEEK_SET);      
    }
    return 1;
  }
  return  0;
}
long find_nline_trunc(FILE *f){  // TODO test if truncated half-file
  fseek(f,0,SEEK_END);
  //change position to SEEK_END - cnt
  int cnt = N_LINES; 
  long pos = 0;
  if(IS_LINES){
    pos = find_nline(f,cnt); //TODO change to find_line // <-???
  }
  else{
    pos = -cnt;	
  }
  return pos;
}


  

int print_file(FILE *f){ 
  char buf [BUF_SIZE];
  memset(buf,0,BUF_SIZE);
  int n = 0;
    while(n = fread(buf,sizeof(char),BUF_SIZE-1,f)){
      n = min(n,BUF_SIZE);
      buf[n] = 0;
      fwrite(buf,sizeof(char),n, stdout);
      memset(buf,0,BUF_SIZE);
  }
}
		 

		 

long find_nline(FILE *f, long n_lines){
  n_lines++; // begining -> (n + 1) * '\n';
  long old = ftell(f);\
  
  fseek(f, 0, SEEK_END);
  char buff[BUF_SIZE + 1];
  
  long n = n_lines;
  long pos = 0; 
  int i = 1;
  long len = BUF_SIZE;
  int start = 0;
  /* FILE NOT ENDED AND n < n__lines */
  while(start != 1 && n != 0 ) {
    if(fseek(f,-BUF_SIZE  * i,SEEK_END)){
      
      // unsuccess
      start = 1;
      len = ftell(f);
      fseek(f,0,SEEK_SET);

      // fseek < 0 => fseek = 0
    }

    len = min(len, BUF_SIZE);
    
    memset(buff,0,BUF_SIZE + 1);

    fread(buff,sizeof(char),len, f);
    buff[len] = 0;
    pos = find_pos(&n,buff);
    if(pos != -1){
      break;
    }
    i++;
  }
  if(pos == -1){
    // fail
    fseek(f,0,SEEK_END);
    pos = ftell(f);
    pos = -pos;
    // restore file position before the call
    fseek(f,old,SEEK_SET);
    
  }
  else{
    // success
    long res_pos = -(BUF_SIZE *(i - 1) + len - pos - 1); // +/-1<-error?
    fseek(f,old,SEEK_SET);
    return res_pos;
  }          
}
// return position of '\n' in buf if #'\n's == n
// otheerwise -1
int find_pos(long *n, char* buf){
  long n_found = 0;
  char* found = NULL;
  while(n_found < *n && (found = strrchr(buf,'\n')) != NULL){
    n_found++;
    *found=0;
  }
  if(n_found == 0){
    return -1;
  }
  if(n_found < *n){
    *n = *n - n_found;
    return -1;
  }
  else if(n_found == *n){
    return found - buf;
  }
}


void print_last_lines(FILE *f, long n){//NOT USED???
  print_last(f,find_nline(f,n));
}

void print_last_bytes(FILE *f, long n){//NOT USED???
  print_last(f, -n);  
}

void print_pos(FILE* f, long pos){
  char buf[BUF_SIZE +1];
  memset(buf,0,BUF_SIZE + 1);
  if(fseek(f,pos,SEEK_END)){
    perror("print_pos fseek error\n");
    printf("pos=%d\n",pos);
  }
  int r = 0;
  while(r=fread(buf,sizeof(char),BUF_SIZE,f)){
    buf[BUF_SIZE]=0;
    fwrite(buf,sizeof(char),r,stdout);
    memset(buf,0,BUF_SIZE + 1);
  }
}

int get_filename(FILE *f,char **name){//for FUTURE versions and FAST computers

  char *proclnk[FNAME_SIZE]={0};
  char *fullname[FNAME_SIZE]={0};
  int fd = fileno(f);
  snprintf(proclnk,FNAME_SIZE-1, "/proc/self/fd/%d", fd);
  int r = readlink(proclnk,fullname,FNAME_SIZE-1);
  if(r <= 0){
    *name=NULL;
    return -1;
  }
  r=min(r,FNAME_SIZE-1);
  fullname[r] = 0;
  char *filename = basename(fullname);
  int len = strnlen(filename,FNAME_SIZE-1);
  *name = malloc((len + 1) * sizeof(len));
  strncpy(*name,filename,len);
  *name[len] = 0;
  return 0;
}


  
///////////////////////////////////////////////////////////
//list_functions
//////////////////////////////////////////////////////////

void add(FILE * f,char *name){
   file_node *added = malloc(sizeof(file_node));
   added->next = NULL;
   added->file = f;
   added->name = name;

   if(HEAD == NULL){
     HEAD = added;
     TAIL = added;
   }
   else{
     TAIL = TAIL->next = added;
   }
 }

 void delete(){
   file_node *l;
   l = HEAD;
   while(l != NULL){
     file_node* t = l -> next;
     free(l);
     l = t;
   }
   HEAD=TAIL=NULL;
 }


  
  
