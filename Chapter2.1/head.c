#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
int print_lines(const char* FILE_NAME, int cnt);
int rev_print(FILE *f, int cnt);
void print_c(char c, int times);
void run(int first_file, int last_file,const char * argv[]);
int main(int argc, char* argv[]){
	if(argc <= 1){
		return 0;
	}
	int oc;
	char *bytes_arg;
	char *lines_arg;
		int q = 1;
	while((oc = getopt(argc,argv,"cnqv")) != -1){
		switch(oc){
			case 'c':
				bytes_arg=optarg;
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
	if(optind<argc){
		run(optind,argc,argv);
	}
	return 0;
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

void run(int first_file, int last_file,const char * argv[]){
	for(int i = first_file; i < last_file;i++){
		print_lines(argv[i],10);
		//print_c('#',80);
	}
}
