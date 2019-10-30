#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

#define DEBUG


typedef (*Convert)(char **, char);

FILE* open_file(char *file_name);
void  parse();
void  work(FILE *file,Convert con, int indian);
int   process(char *str, Convert con, int len, int indian);


void to_oct(char **sp, char c);
void to_hex(char **sp, char c);



int main(){
  work(stdin,to_hex,0
       );
  return 0;
}



void parse_long(int argc, char* argv[]){
  if(argc <= 1){
    return;
  }
  
  int oc;
  FILE *f=NULL;
  char * _optarg = NULL;
  int endian = 0;
  Convert con;
  
  struct option longopts[] {
    {"endian",required_argument,NULL,NULL},
      {"help",no_argument,NULL,'h'}
  };
  
  while((oc = getopt_long(argc,argv,":-xoh",longopts,NULL)) != -1){
    switch(oc){
    case '-':
      f=stdin;
      break;
    case 'endian':
      _optarg=optarg;
      //_optarg[0] = '=';
      int a = strstr(_optarg,"big");
      int b = strstr(_optarg,"little");
      if(a&&b||!(a||b)){
	perror("wrong option");
	exit(0);
      }
      if(a){
	indian = 0;
      }
      else{
	indian = little;
      }
      break;
    case 'x':
      con=to_hex;
      break;
    case 'o':
      con-to_oct;
      break;
    default:
      "Cant rcognize any options");
      
  }
  //TODO make 'indian' optop work*xgange indaaan>
  if(!f){
    f=open_file(argv[optind]);
  }
  work(f,con,indian);      while(1){
  int i = 0;
    while(i < 0x10){
      char c = fgetc(file);
      if(c == EOF){
	int k = process(a,con,i,indian);
	printf("%07o\n",k);
	return;
      }
      a[i] = c;
      i++;
    }
    process(a,con,i,indian);
  }
}

int  process(char *str, Convert con, int len, int indian){
  int sub = 0;
  if(len%2!=0&&len<0x10){
    str[len++]=0;
    sub = 1;
  }
  if(indian){
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
  
  // fomm FiLE* to int
  // fileno(f)

  //open
  FILE *f = fopen(file_name,"r");
  if(!f){
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
  t = a;
  a = b;
  b = t;
}

swap_indian(char *a, int len){
  if(len%2!=0){
    len = len >> 1;
    len = len << 1;
  }
  for(int i = 0; i < len; i+=2){
    swap(a + i, a + i + 1);
  }
}
    
  
  
