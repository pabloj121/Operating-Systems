#include<unistd.h> 
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include<stdio.h>
#include<errno.h>
#include<dirent.h>
#include<string.h>

int main(int argc, char* argv[]){
	pid_t pid;
	int fd[2];
	char c;
	int bytesleidos;
	DIR *directorio;
	struct stat atributos;
	struct dirent *entrada;
	char ruta[512], buffer[512];

	if(pipe(fd) < 0){
		perror("Error\n");
	}

	if((pid=fork()) < 0){
		perror("Error"), exit(1);
	}
	else if(pid == 0){//hijo
		close(fd[1]);
		//if(bytes = read(fd[0], ,1) < 0)
			perror("Error"), exit(1);
		printf("%c\n",c );
	}
	else{//padre
		if((directorio = opendir(".")) != NULL){
			perror("Error al abrir el archivo\n");
			exit(1);
		}

		while((entrada=readdir(directorio)) != NULL){
			sprintf(ruta, "%s/%s", argv[1], entrada->d_name);

			if(stat(rutadirectorio, &atributos)<0) {
						perror("Error");
						exit(1);
			}

			if(S_ISREG(atributos.st_mode)){
				if((fd=open(ruta,O_RDONLY))<0){
					perror("....");
					exit(1);
				}				

				while((bytesleidos = read(fd, buffer, 256*sizeof(char))) >0 ){
					if(write(fd1, buffer, bytesleidos) < 0){
						perror("...."), exit(1);
					}
				}
				
				close(fd[0]);
				c = 97;
				if(write(fd[1], &c, sizeof(char)) <0)
					perror("Error"), exit(1);
			}
		}
	}
}