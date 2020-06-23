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
#define ARCHIVO_FIFO "CAUCE"

int main(int argc, char const *argv[]){

	if(argc!=2){
		printf("ERROR: El formato es ./NProcesos n c [1,10]\n");
		exit(1);
	}

	int i,j,numero,estado,N;
	char buffer[] = "0"; //valor inicial a incrementar
	pid_t PID;

	N = atoi(argv[1]);

	umask(0); //Creo un cauce de comunicacion de tipo FIFO
	mknod(ARCHIVO_FIFO,S_IFIFO|0666,0);
	int fd = open(ARCHIVO_FIFO,O_RDWR);

	printf("[Proceso padre] Valor inicial: %s.\n\n", buffer);
	write(fd,buffer,strlen(buffer)); //Lo escribo en un cauce de politica FIFO a traves del cual se comunicarán los procesos hijos

	for(i=0;i < N;i++){
		if((PID = fork())<0){
			perror("ERROR en fork");
			exit(1);
		}
		if(PID==0){
			read(fd,buffer,strlen(buffer)); //El flujo de entrada por defecto de los hijos será el cauce
			numero = atoi(buffer);
			if(numero<9){
				printf("[Proceso %d] con PID: %d, incremento %d a %d.\n",i,getpid(),numero,numero+1);
				numero++;
			}
			else{
				printf("[Proceso %d] con PID: %d, no puedo incrementar el último dato leido, ya es 9.\n",i,getpid());
				write(fd,buffer,strlen(buffer)); //Escribo el numero incrementado para que el siguiente hijo lo pueda leer
				exit(0);
			}

			sprintf(buffer,"%d", numero);

			write(fd,buffer,strlen(buffer)); //Escribo el numero incrementado para que el siguiente hijo lo pueda leer
			exit(0);
		}
		else{
			PID = wait(&estado);//El padre espera al hijo
			printf("[Proceso padre] con PID: %d espero a mi hijo %d con PID: %d.\n\n",getpid(),i,PID);
		}
	}

	unlink(ARCHIVO_FIFO); //Borro el cauce porque solo sirve para este programa

	exit(0);
}