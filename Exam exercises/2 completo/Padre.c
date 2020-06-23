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

	char pathname[500];
	pid_t PID;
	int estado,numero;
	char buffer[20];

	if(argc==2){
		strcpy(pathname,argv[1]);
	}
	else
		strcpy(pathname,".");

	int fd[2];
	pipe(fd);

	PID = fork();

	if(!PID){
		printf("Introduce un numero entre el 0 y el 9\n");
		close(fd[0]);
		dup2(fd[1],1);
		do{
			read(0,buffer,20);
			numero = atoi(buffer);
		}while(numero<0||9<numero);
		sprintf(buffer,"%d", numero);
		write(fd[1],buffer,strlen(buffer));
	}
	else{
		wait(&estado);
		close(fd[1]);
		dup2(fd[0],0);
		execlp("./LeerDir","LeerDir",pathname,NULL);
	}

	exit(0);
}