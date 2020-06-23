/*2 argumentos
1 nombre directorio
1 nombre fichero
recorrer entradas del directorio y escribir en ese fichero 
el nombre de todos los archivos regulares*/

#include<unistd.h>  /* POSIX Standard: 2.10 Symbolic Constants <unistd.h>
		     */
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>  /* Primitive system data types for abstraction	\
			   of implementation-dependent data types.
			   POSIX Standard: 2.6 Primitive System Data Types
			   <sys/types.h>
		       */
#include<sys/stat.h>
#include <fcntl.h>
#include<stdio.h>
#include<errno.h>
#include<dirent.h>
#include<string.h>			

			int main(int argc, char *argv[]){
				if(argc !=3){
					printf("Error de argumentos\n");
					exit(1);
				}

				int fd;
				struct stat atributos;
				DIR *directorio;
				struct dirent *entrada;
				char rutadirectorio[512];
				//, rutafichero[512];
				char buffer[512];

				// Parametro 1
				if((directorio = opendir(argv[1]))==NULL){
					perror("Error al abrir el directorio"),
					exit(1);
				}
				// Parametro 2
				if((fd=open(argv[2],O_WRONLY|O_TRUNC|O_CREAT, S_IRWXU|S_IRWXG))<0){
					perror("....");
					exit(1);
				}

				while((entrada=readdir(directorio))!=NULL){
					//ruta = argv[1]
					sprintf(rutadirectorio, "%s/%s",argv[1],entrada->d_name);
					if(stat(rutadirectorio, &atributos)<0) {
						perror("Error");
						exit(1);
					}
					if(S_ISREG(atributos.st_mode) && !(S_ISDIR(atributos.st_mode)))
							//buffer = rutadirectorio;
							if(write(fd,rutadirectorio,strlen(rutadirectorio))<0){
								perror("Error al escribir");
							}

							printf("Entrada : %s", entrada->d_name);
							printf("\n");
				}
			}