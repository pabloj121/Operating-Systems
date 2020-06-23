/*-recibre como arg 2 directorios
-copiar todos aquellos ficheros regulares que tengan permisos de escritura para el usuario del primer directorio al 2ª directorio
respetando el nombre del fichero original y los permisos del fichero original*/
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
				if(argc !=3){
					// no pongo perror porque no hemos hecho ninguna llamada al sistema
					//porque mostrar el error de la ultima llamada
					// al sistema que se hizo
					printf("Error de argumentos\n");
					exit(1);
				}
				
				int fd, fd1, bytesleidos;
				struct stat atributos;
				DIR *directorio;
				struct dirent *entrada;
				char rutadirectorio[512], rutadirectorio2[512];
				//, rutafichero[512];
				char buffer[512];

				// Parametro 1
				if((directorio = opendir(argv[1]))==NULL){
					perror("Error al abrir el directorio"),
					exit(1);
				}

				while((entrada=readdir(directorio))!=NULL){
					//ruta = argv[1]
					sprintf(rutadirectorio, "%s/%s",argv[1],entrada->d_name);
					sprintf(rutadirectorio2, "%s/%s",argv[2],entrada->d_name);
					
					if(stat(rutadirectorio, &atributos)<0) {
						perror("Error");
						exit(1);
					}

					if(S_ISREG(atributos.st_mode) && ((atributos.st_mode & S_IWUSR)== S_IWUSR)){							
								if((fd=open(rutadirectorio,O_RDONLY))<0){
									perror("....");
									exit(1);
								}
								// Parametro 2
								if((fd1=open(rutadirectorio2,O_WRONLY|O_TRUNC|O_CREAT, atributos.st_mode))<0){
									perror("....");
									exit(1);
								}

								while((bytesleidos = read(fd, buffer, 256*sizeof(char))) >0 ){
									if(write(fd1, buffer, bytesleidos) < 0)
										perror("...."), exit(1);
								}

								close(fd); close(fd1);							
					}
			}
}
