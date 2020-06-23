/*1 argumento directorio
a cada fichero regular de ese directorio añadir escritura a otros*/
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

int main(int argc, char *argv[]){
				if(argc !=2){
					printf("Error de argumentos\n");
					exit(1);
				}

				int fd;
				struct stat atributos;
				DIR *directorio;
				struct dirent *entrada;
				char rutadirectorio[512];
				umask = 0; // con poner esto estoy diciendo que cualquier permiso que le 
						// de al archivo se ponga si o si
				// Parametro 1
				if((directorio = opendir(argv[1]))==NULL){
					perror("Error al abrir el directorio"),
					exit(1);
				}

				while((entrada=readdir(directorio))!=NULL){	// si null no hay mas entradas
					//ruta = argv[1]
					sprintf(rutadirectorio, "%s/%s",argv[1],entrada->d_name); // como estamos intentado acceder a los ficheros de un directorio
					if(stat(rutadirectorio, &atributos)<0){
						perror("Error");
						exit(1);
					}
					if(S_ISREG(atributos.st_mode) && !(S_ISDIR(atributos.st_mode))){
							//buffer = rutadirectorio;
							//atributos.st_mode = atributos.st_mode | S_IWOTH;
							if(chmod(rutadirectorio,atributos.st_mode | S_IWOTH)<0){
								perror("Error cambiando permisos...");
							}
					}
							printf("Entrada : %s", entrada->d_name);
							printf("\n");
				}
}