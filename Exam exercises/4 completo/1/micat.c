#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include <sys/types.h>
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
	int fd1,fd2;

	if( ( strcmp(argv[1],"-") == 0 ) && ( strcmp(argv[2], "-" ) != 0) ){
		read(0,buffer,256);
		fd1=open(argv[2],O_WRONLY);
		write(fd1,buffer,strlen(buffer));
	}

	if( ( strcmp(argv[1],"-") != 0 ) && ( strcmp(argv[2], "-" ) == 0) ){
		fd1=open(argv[1],O_RDWR);
		read(fd1,buffer,256);
		write(1,buffer,strlen(buffer));
	}

	if( ( strcmp(argv[1],"-") != 0 ) && ( strcmp(argv[2], "-" ) != 0) ){
		fd1=open(argv[1],O_RDWR);
		fd2=open(argv[2],O_RDWR);
		read(fd1,buffer,256);
		write(fd2,buffer,strlen(buffer));
	}


	exit(0);
}