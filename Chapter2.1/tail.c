//TODO -> BUGS

//#define DEBUG
//#define TEST

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

#define NLINES 10

#define min(x, y)  ((x) < (y) ? (x) : (y))

typedef void (*Fp) (FILE *f, long n);


int find_pos(long *n, char* buf);
long find_nline(FILE *f, long n_lines);
void print_last_lines(FILE *f, long n);
void print_last_bytes(FILE *f, long n);
void print_last(FILE* f, long pos);
void follow_file(const char *filename);
//void run(int first_file, int last_file,char *  argv[], long cnt, Fp fp); 
void run(int first_file, int last_file,char *  argv[], long cnt,int is_lines);
int main(int argc, char *argv[]){

  /*
  FILE *f = fopen(argv[1],"rt");
  long n = NLINES;
  if(argc > 2){
    n = atol(argv[2]);
  }

#ifdef DEBUG
  long pos = ftell(f);
  fseek(f,0,SEEK_END);
  printf("file_size=%ld\n",ftell(f));
  fseek(f, pos, SEEK_SET);
#endif
  //print_last_lines(f,n);
  print_last_bytes(f,n);
  */
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
    //res = atoi(p+1);
    nptr = p+1;
  }
  else{
    res = strtol(arg,&endptr,10);
    //res = atoi(arg);    
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
  //Fp fp;
  if(argc <= 1){
    return;
  }
  int is_lines = 0;
  int oc;
  struct  option longopts[] = {
			       {"bytes",required_argument,NULL,'c'},
			       {"lines",required_argument,NULL,'n'},
			       {"follow",no_argument,NULL,'f'},
			       {"help", no_argument,NULL,'h'}
  };

  
  while((oc = getopt_long(argc,argv,":c:n:fh",longopts,NULL)) != -1){
    switch(oc){
    case'c':   
      //fp = print_last_bytes;
      is_lines = 0;
      break;
    case 'n':
      //fp =  print_last_lines;
      is_lines = 1;
      break;
    case 'f':
      follow=1;
      break;
  default:
    printf("***OOps we are here***\n");
    return;
    }
  }
  /*
  long cnt = convert(optarg);
  if( cnt == -1 ){
    cnt = NLINES;
  }
  */
  long  cnt = NLINES;

    
  
  // Print files according to opts
  if(optind<argc){
    if(follow){
      follow_file(argv[optind]);
    }
    else{
      run(optind,argc,argv,cnt,is_lines);
    }
  }

}

void run(int first_file, int last_file, char * argv[], long cnt, int is_lines ){
#ifdef DEBUG
  printf("run_cnt = %d\n",cnt);
#endif
  for(int i = first_file; i < last_file;i++){
    long pos = 0;
    //BEGINING work with file;
#ifdef DEBUG
    printf("Opening file \"%s\"\n",argv[i]);
#endif
    FILE *f = fopen(argv[i],"r");  
    if(!f){
      return;
    };
#ifdef DEBUG
    printf("File \"%s\" opened\n",argv[i]);
#endif
    if(is_lines){
     pos = find_nline(f,cnt);
    }
    else{
      pos = -cnt;
    }
    print_last(f,pos);
  }
}

void follow_file(const char *filename){
  FILE *f = fopen(filename,"rt");
  print_last_lines(f, NLINES);
  char buf [BUF_SIZE];
      while(1){	
	while(fread(buf,sizeof(char),BUF_SIZE-1,f)){
	  buf[BUF_SIZE] = 0;
	  fwrite(buf,sizeof(char),BUF_SIZE -1, f);
	}
      }
}



// finds begining  n-th '\n' starting from EOF);
// if success first character of n-th line in FILE
// if fail -1
long find_nline(FILE *f, long n_lines){
  // search for begining of line (after '\n')
  n_lines++; // begining -> (n + 1) * '\n';
  long old = ftell(f); // SEEK_SET begining

  fseek(f, 0, SEEK_END);
  char buff[BUF_SIZE + 1];
  
  long n = n_lines;
  long pos = 0;
  int i = 1; //position before start of reading in
  long len = BUF_SIZE;
  int start = 0;
  /* FILE NOT ENDED AND n < n__lines */
  while(start != 1 && n != 0 ) {
    // ????
    if(fseek(f,-BUF_SIZE  * i,SEEK_END)){
      // if(fseek(f, -BUF_SIZE  * i,SEEK_CUR)){
      
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
    //TODO
    //count from SEEK_SET
    //long res_pos = ftell(f) - (len - pos - 1);
    //TODO
    //cont from SEEK_END
    long res_pos = -(BUF_SIZE *(i - 1) + len - pos - 1); // +/-1<-error?
#ifdef DEBUG
    printf("res_pos=%ld\n",res_pos);
#endif
    //^TODO^
    
    // restore file position before the call
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
    buf[found-buf] = 0; // TODO change -> *found
  }
  if(n_found == 0){
    return -1;
  }
  if(n_found < *n){
    *n = *n - n_found;
    return -1;
  }
  else if(n_found == *n){
    return found - buf; // TODO change -> *found
  }
}


void print_last_lines(FILE *f, long n){
  print_last(f,find_nline(f,n));
}

void print_last_bytes(FILE *f, long n){
  print_last(f, -n);  
}

void print_last(FILE* f, long pos){
  char buf[BUF_SIZE +1];
  memset(buf,0,BUF_SIZE + 1);

#ifdef DEBUG
  printf("LALA in print_last LALA\n");
  printf("print_last pos = %ld\n",pos);
#endif

  
  if(fseek(f,pos,SEEK_END)){
    perror("print_last fseek error\n");
  }

#ifdef DEBUG
  printf("ftell in print_last = %ld\n", ftell(f));
#endif
  int r = 0;
  while(r=fread(buf,sizeof(char),BUF_SIZE,f)){
    buf[BUF_SIZE]=0;
    fwrite(buf,sizeof(char),r,stdout);
    // fflush(stdout);
    memset(buf,0,BUF_SIZE + 1);
  }
}
  

  
