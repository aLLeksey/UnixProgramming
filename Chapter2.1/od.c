#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<getopt.h>
#include<string.h>

#define DEBUG


/*
USAGE 
od - 
^from std io
od FILENAME
^from FILENAME

 */

typedef void(*Convert)(char **, char);
typedef enum endian {big=0,little=1} endian;


FILE* open_file(char *file_name);
void  parse();
void  work(FILE *file,Convert con, endian e);
int   process(char *str, Convert con, int len, endian e);


void to_oct(char **sp, char c);
void to_hex(char **sp, char c);



int main(char argc, char* argv[]){
  //work(stdin,to_hex,0);
  parse_long(argc,argv);
  return 0;
}



void parse_long(int argc, char* argv[]){
  if(argc <= 1){
    return;
  }
  
  int oc;
  FILE *f=NULL;
  char * _optarg = NULL;
  char *a = NULL;
  char *b = NULL;
 
  endian e = big;
  Convert con;


  enum{
    OPT_ARGUMENT1 = 10000,
    OPT_ARGUMENT2 = 10001,
    OPT_ARGUMENT3
  };
  
  struct option longopts[] = {
    {"endian",required_argument,NULL,OPT_ARGUMENT1},
    {"help",no_argument,NULL,'h'},
    {"-",no_argument,NULL,OPT_ARGUMENT2},
    {NULL, 0, 0, 0}
  };

  /*
int getopt_long(int argc, char * const argv[],
	const char *optstring,
	const struct option *longopts, int *longindex);

int getopt_long_only(int argc, char * const argv[],
	const char *optstring,
	const struct option *longopts, int *longindex);
  */
  while((oc = getopt_long_only(argc,argv,"-hox",longopts,NULL)) != -1){
    switch(oc){
    case '-':
      f=stdin;
      printf("BB\n");
      break;
      
    case OPT_ARGUMENT1:
      _optarg=optarg;;
      a = strstr(_optarg,"big");
      b = strstr(_optarg,"little");
      if(a&&b||!(a||b)){
	perror("wrong option");
	exit(0);
      }
      if(a){
        e = big;
      }
      else{
	e = little;
      }
      break;
      
    case 'x':
      con=to_hex;
      break;
      
    case 'o':
      con=to_oct;
      break;

    case 'h':case'?':
      printf("Options are \n"
"-                  :input from stdin\n"
"file_name[s]         :input from file name[s]\n"
"--endian={big;little}:set endian\n"
"-x                   :to hexadecimal\n"
"-o                   :to octal\n"
"-d                   :to decimal\n"
"-a                   :select named characters, ignoring high-order bit\n"
"-c                   :select printable characters or backslash escapes\n");
      break;
    default:
      printf("%c %d\n",oc,oc);
      printf("Cant recognize any options");
      exit(0);
      
    }
  }
  
  if(!f){
    printf("Lala f == %d\n",f);
    f=open_file(argv[optind]);
  }
  //work(f,con,e);
  while(1){
  int i = 0;
    while(i < 0x10){
      char c = fgetc(f);
      if(c == EOF){
	int k = process(a,con,i,e);
	printf("%07o\n",k);
	return;
      }
      a[i] = c;
      i++;
    }
    process(a,con,i,e);
  }
}

int  process(char *str, Convert con, int len, endian e){
  int sub = 0;
  if(len%2!=0&&len<0x10){
    str[len++]=0;
    sub = 1;
  }
  if(e){
    swap_indian();
  }
    
  static int i = 0;
  printf("%07o ",i);

  int j = 0;
  while(j < 0x10 && j < len){
    char c = str[j];
    char *s = NULL;
    con(&s,c);
    printf("%s",s);
    if(j%2!=0){
      printf(" ");
    }
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
  if(sub){
    i--;
  }
  
  return  i;
}

FILE* open_file(char *file_name){
  FILE *f = fopen(file_name,"rw");
  if(!f){
  // fomm FiLE* to i
    perror("Cant open file"); // %s",file_name);
    exit(0);
  }
  return f;
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
void swap(char *a, char *b){
  char t;
  t = *a;
  *a = *b;
  *b = t;
}

void swap_indian(char *a, int len){
  if(len%2!=0){
    len = len >> 1;
    len = len << 1;
  }
  for(int i = 0; i < len; i+=2){
    swap(a + i, a + i + 1);
  }
}
    
  
  
