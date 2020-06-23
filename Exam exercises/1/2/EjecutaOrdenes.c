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

	int fd = open(ARCHIVO_FIFO,O_RDWR);
	pid_t PID;
	int estado;

	char buffer[] = "aa";

	while(strcmp(buffer,"es")){
		read(fd,buffer,2);
		if((PID=fork())==0)
			execlp(buffer,buffer,NULL);
		PID = wait(&estado);
	}

	unlink(ARCHIVO_FIFO);

}