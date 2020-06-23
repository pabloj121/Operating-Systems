#include<unistd.h>  /* POSIX Standard: 2.10 Symbolic Constants <unistd.h>
		     */
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>
#include<stdio.h>
#include<errno.h>
#include<dirent.h>
#include<string.h>

int main(int argc, char const *argv[])
{
	pid_t pid;
	DIR *dir;
	struct dirent* entrada;
	int fd[2];
	struct stat attr;

	if((pipe(fd)) <0){
		perror("Error al abrir el archivo"), exit(1);
	}

	if((pid = fork()) < 0){
		perror("No se pudo crear el hijo"); exit(1);
	}
	else if(pid==0){
		close(fd[0]);
		if((dir = opendir(".")) == NULL){
			perror("No se pudo abrir el directorio actual");
			exit(1);
		}

		while((entrada = readdir(dir)) != NULL){
			if(stat(entrada->d_name, &attr) <0){
				perror("No se pudo recuperar la informacion");
				exit(1);
			}

			if(S_ISREG(attr.st_mode)){
				printf("Inodo: %d, uid: %d\n", attr.st_ino, attr.st_uid);

				if(write(fd[1],entrada->d_name, sizeof(entrada->d_name)) < 0){
					perror("No se pudo escribir en el cause"), exit(1);
				}
			}
		}
	}
	else{
		close(fd[1]);
		char nombre_archivo[256], datos[512];
		int fd_archivo, bytesleidos;

		while(read(fd[0], nombre_archivo, sizeof(char)*256) > 0){
			if((fd_archivo = open(nombre_archivo, O_RDONLY)) < 0){
				perror(nombre_archivo);
				exit(1);
			}

			while((bytesleidos = read(fd_archivo, datos, sizeof(char)*512)) > 0){
				if(write(STDOUT_FILENO, datos, bytesleidos) < 0){
					perror("No se pudo mostrar por pantalla");
					exit(1);
				}
			}

			close(fd_archivo);
		}
	}

	return 0;
}