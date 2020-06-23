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
				if(argc !=2){
					printf("Error de argumentos");
					exit(1);
				}

				struct stat atributos;
				DIR *directorio;
				struct dirent *entrada;
				char ruta[512];

				if((directorio = opendir(argv[1]))==NULL){
					perror("Error al abrir el directorio"),
					exit(1);
				}

				while((entrada=readdir(directorio))!=NULL){
					//ruta = argv[1]
					sprintf(ruta, "%s/%s",argv[1],entrada->d_name);
					if(stat(ruta, &atributos)<0) {
						perror("Error");
						exit(1);
					}
					if(S_ISREG(atributos.st_mode))
							printf("Entrada : %s", entrada->d_name);
							printf("\n");
				}
			}