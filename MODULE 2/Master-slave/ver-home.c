#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char* argv[]){
    int fd, ret, pid;
    struct stat atributos;
    DIR *directorio;
    struct dirent *entrada;
    char escritorio[1024], rutadirectorio[1024];
    char *home = getenv("HOME");    

    sprintf(escritorio, "%s/Escritorio", home);
    
    if ((directorio = opendir(escritorio)) == NULL){
        perror("Error al abrir el directorio"),
        exit(1);
    }

    while ((entrada = readdir(directorio)) != NULL){
         // si null no hay mas entradas
        //ruta = argv[1]
        sprintf(rutadirectorio, "%s/%s", argv[1], entrada->d_name); // como estamos intentado acceder a los ficheros de un directorio
        
        if (stat(rutadirectorio, &atributos) < 0){
            perror("Error");
            exit(1);
        }
        if (S_ISLNK(atributos.st_mode)){
            printf("%d\n", "%d\n", atributos.st_uid, atributos.st_gid);

            if((pid=fork()) < 0){
                perror("Error creando hijo\n");
                exit(1);
            }
            else if(pid == 0){
                execlp("./ver-origen", "ver-origen", rutadirectorio, NULL);
                perror("Error ejecutando ver-origen");
                exit(1);
            }
            wait(&ret);

            if(ret == EXIT_SUCCESS){
                if((pid = fork()) < 0){
                    perror("Error creando segundo hijo\n");
                    exit(1);
                }
                else if(pid == 0){
                    execlp("mountpoint", "mountpoint", NULL);
                    perror("Error en exec de mountpoint");
                    exit(1);
                }
                wait(NULL);
            }
        }
        printf("\n");
    }
}