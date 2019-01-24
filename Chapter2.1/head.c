#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
int print_lines(const char* FILE_NAME, int cnt);
int rev_print(FILE *f, int cnt);
void print_c(char c, int times);

int main(int argc, char* argv[]){
	if(argc <= 1){
		return;
	}
	for(int i=1; i < argc;i++){
		print_lines(argv[i],10);
		//print_c('#',80);
	}
	
	return 0;
}

int print_lines(const char* FILE_NAME, int cnt){
	FILE *f = fopen(FILE_NAME,"r");
	if(f==0)return;
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
	
