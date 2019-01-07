#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
       
#define SIZE 1000
int main(int argc, char**argv){
	if(argc<1){
		return 0;
	}
	int f = open(argv[1], O_RDONLY);
	
	char buf[SIZE];
	size_t k = 0;
	while(k = read(f,buf,SIZE-1)){
		buf[SIZE-1] = 0;
		if(k < SIZE){
				buf[k] = 0;
		}
		printf("%s",buf);
	}
}
