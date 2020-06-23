#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char const *argv[]){

	if(argc!=3){
		printf("ERROR: El formato es ./micat f|- d|-");
		exit(1);
	}

	char buffer[256];
	int fd;

	if( ( strcmp(argv[1],"-") == 0 ) && ( strcmp(argv[2], "-" ) != 0) ){
		close(1);
		fd=open(argv[2],O_WRONLY);
		dup2(fd,1);
		execlp("./leede0Escribeen1","leede0Escribeen1",NULL);
	}

	if( ( strcmp(argv[1],"-") != 0 ) && ( strcmp(argv[2], "-" ) == 0) ){
		close(0);
		fd=open(argv[1],O_RDWR);
		dup2(fd,0);
		execlp("./leede0Escribeen1","leede0Escribeen1",NULL);
	}

	if( ( strcmp(argv[1],"-") != 0 ) && ( strcmp(argv[2], "-" ) != 0) ){
		execlp("./leede0Escribeen1","leede0Escribeen1",NULL);
	}


	exit(0);
}