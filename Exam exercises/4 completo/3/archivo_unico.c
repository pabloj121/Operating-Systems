/*
 * lockit.c - Establece el bloqueo en un archivo
 */
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

/* Establece un bloqueo de tipo en el descriptor fd */
void setlock(int fd, int type);
 
int main ( int argc, char *argv[] )
{
		int fd;
		char buffer[2];
		printf("%d\n", getpid());
		sprintf(buffer,"%d", getpid());
		/* Abre el archivo */
		fd = open(argv[1], O_RDWR | O_CREAT, 0666);
		if (fd < 0) {
			perror("open");
			exit(EXIT_FAILURE);
		}
		
		/* Establece un bloqueo de escritura */
		setlock(fd, F_WRLCK);
		printf("PID %d bloqueado para escritura %s\n", getpid(), argv[1]);
		sleep(20);
 		getchar();
    	close(fd); 
 		printf("Fin de la ejecución\n");

		return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
 
void setlock(int fd, int type)
{
		struct flock lock;
		char msg[80];
 
		/* Describe el bloqueo que queremos */
		lock.l_whence = SEEK_SET;
		lock.l_start = 0;
		lock.l_len = 1; /* bloquea un solo bit */
 
		while (1) {
			lock.l_type = type;
			/* Bloqueo establecido y vuelta al que llama */
			if ((fcntl(fd, F_SETLK, &lock)) == 0)
				return;
			else
				printf("Hay una unica instancia\n");
 
			/* Busca por qué no podemos establecer el bloqueo */
			fcntl(fd, F_GETLK, &lock);
			if(lock.l_type == F_WRLCK) {
				sprintf(msg, "bloqueo de escritura ya establecido por %d\n", lock.l_pid);
			}
			puts(msg);
			getchar();
		}
}