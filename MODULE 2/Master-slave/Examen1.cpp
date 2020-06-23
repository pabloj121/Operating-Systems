#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>

int main(){

	pid_t pid;
	DIR* dir;
	struct dirent* ent;
	struct stat attr;
	int fd[2];

	if(pipe(fd) < 0){
		perror ("No se puede abrir el pipe");
		exit(1);
	}

	if ((pid=fork())<0) {
		perror ("No se pudo crear el hijo (aborto natural)");
		exit(1);
	}

	else if(pid==0){
		if((dir = opendir(".")) == NULL){
			perror("No se pudo abrir el directorio actual");
			exit(1);
		}
		while((ent =readdir(dir)) != NULL){
			if(stat(ent->d_name, &attr) <0){
				perror("No se pudo recuperar la información del fichero");
				exit(1);

			}
			if(S_ISREG(attr.st_mode)) {
				printf("Inodo: %ld, uid: %ld\n", attr.st_ino, attr.st_uid);
				if(write(fd[1], ent->d_name, sizeof(ent->d_name))< 0){
					perror("No se pudo escribir en el cauce");
					exit(1);
				}
			}
		}
	}

else{
	close(fd[1]);
	char nombre_archivo[256], datos[512];
	int fd_archivo, bytes_leidos;
	while(read(fd[0], nombre_archivo, sizeof(char)*256)>0){
		if((fd_archivo = open(nombre_archivo, O_RDONLY)) < 0){
			perror("No se puede abrir el archivo");
			exit(1);
		}
		while((bytes_leidos = read(fd_archivo, datos, sizeof(char)*512)) > 0){
			if(write(STDOUT_FILENO, datos, bytes_leidos)<0){
				perror("ńo se pudo mostrar por pantalla");
				exit(1);
			}
		}
		close(fd_archivo);
	}
}

}