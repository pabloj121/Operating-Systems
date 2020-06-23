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

#define ARCHIVO_FIFO "COMANDOS"

int main(){

	umask(0);
	mknod(ARCHIVO_FIFO,S_IFIFO|0666,0);

	int fd = open(ARCHIVO_FIFO,O_RDWR);

	char buffer[] = "aa";

	while(strcmp(buffer,"es")){
		read(0,buffer,2);
		write(fd,buffer,2);
	}

}