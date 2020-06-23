#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>

#define ejecucion(mode) ((((mode) & S_IRWXU) == 00700))

void cuenta(DIR *direct, char pathname[],int* cantidad){
	struct stat atributos;
	struct dirent *ed;
	char cadena[500];

	while((ed=readdir(direct)) != NULL){
		if (strcmp(ed->d_name, ".") != 0 && strcmp(ed->d_name, "..") != 0){
			sprintf(cadena,"%s/%s",pathname,ed->d_name);
			if(stat(cadena,&atributos) < 0) {
				printf("\nError al intentar acceder a los atributos de archivo");
				perror("\nError en stat");
				exit(-1);
			}
				(*cantidad)++;
		}
	}
	closedir(direct);
}

void lee_dir(DIR *direct, char pathname[],int entradas){

	struct stat atributos;
	struct dirent *ed;
	char cadena[500];
	int size;
	int nodo;
	long int permisos;
	while(((ed=readdir(direct)) != NULL) && (entradas > 0)){
		if (strcmp(ed->d_name, ".") != 0 && strcmp(ed->d_name, "..") != 0){
			sprintf(cadena,"%s/%s",pathname,ed->d_name);
			stat(cadena,&atributos);
			size = atributos.st_size;
			nodo = atributos.st_ino;
			if(S_ISDIR(atributos.st_mode)){
				if(ejecucion(atributos.st_mode))
					printf("%s|%d|%dKB|directorio|con todos los permisos\n", ed->d_name,nodo,size);
				else
					printf("%s|%d|%dKB|directorio|sin todos los permisos\n", ed->d_name,nodo,size);
			}
			else{
				if(ejecucion(atributos.st_mode))
					printf("%s|%d|%dKB|regular|con todos los permisos\n", ed->d_name,nodo,size);
				else
					printf("%s|%d|%dKB|regular|sin todos los permisos\n", ed->d_name,nodo,size);
			}
			entradas--;
		}
	}
	closedir(direct);

}

int main(int argc, char const *argv[]){
	
	DIR *direct;
	char pathname[500];
	int dir=0,r=0;

	if(argc==2){
		strcpy(pathname,argv[1]);
	}
	else
		strcpy(pathname,".");

	char buffer[20];

	if((direct=opendir(pathname)) == NULL){
		printf("\nError al abrir directorio\n");
		exit(1);
	}
	int cantidad=0;
	cuenta(direct,pathname,&cantidad);
	printf("Numero de archivos: %d\n", cantidad);
	
	read(0,buffer,20);

	int numero = atoi(buffer);

	if(!numero){
		printf("El numero introducido es 0 se cierra el programa\n");
		exit(0);
	}

	if(numero > cantidad){
		printf("El numero introducido es demasiado grande se cierra el programa\n");
		exit(0);
	}

	if((direct=opendir(pathname)) == NULL){
		printf("\nError al abrir directorio\n");
		exit(-1);
	}
	lee_dir(direct,pathname,numero);

	exit(0);
}