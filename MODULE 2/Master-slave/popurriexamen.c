// popurri examen maria angustias
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


// si pid 0 es el hijo

int main(int argc, char* argv[]){
    int pid1, pid2, ret;
    struct stat atributos;
    DIR *directorio;
    struct dirent *entrada;
    char carpeta[1024], ruta[1024];
    int fd[2];   

    sprintf(carpeta, "%s/tmp/chequeos");     //, chequeos);
    if (pipe(fd1)){
        perror("No se puede abrir el pipe");
        exit(1);
    }
    if((fd_dir = opendir("/tmp/chequeos")) == NULL)
    
    while((entrada = readdir(directorio)) != NULL){
        sprintf(ruta, "%s%s", argv[1], entrada->d_name);

        strcpy(ruta_ejec, "/tmp/chequeos");
        strcpy(ruta_ejec, entrada->d_name);
        if(stat(ruta, &atributos) < 0){
            perror("Error al ejecutar stat\n");
            exit(1);
        }

        if(S_ISREG(atributos.st_mode)){
            execlp(ruta_ejec, entrada->d_name, argv[1], NULL);
            perror("Error intentando ejecutar archivo regular\n");
            exit(EXIT_FAILURE);
        }

        if((pid = fork()) < 0){

        }
        else if(pid == 0){
            
        }
    }
      

    // ahora tenemos las entradas de la tabla de archivos abiertos "originales"
    // más los 2 pipes
    if((pid1 = fork) < 0){
        perror("Error creando primer hijo");
        exit(1);
    }
    else if(pid1 == 0){ 
        close(fd1[0]);
        dup2(fd1[1], STDOUT_FILENO);
        execlp("ls", "ls", "-ld", argv[1], NULL);
        perror("Error ejecutando ls...");
        exit (1);
    }

    if((pid2=fork()) < 0){
        perror("Error creando el segundo hijo");
        exit(1);
    }
    else if(pid2 == 0){ // cut -d">" -f2
        // redirigimos la entrada a la salida del primero
        close(fd1[1]);
        if(dup2(fd1[0], STDIN_FILENO) < 0){
            perror("Error intentando duplicar entrada de la tabla de archivos");
            exit(1);
        }
        //execlp("./esclavo", "esclavo", argv[1], cadenanum1, NULL);
        execlp("cut", "cut", "-d", ">", "-f2", NULL);
        perror("Error al hacer el exec\n");
        exit(1);
    }
    
    close(fd1[0]);
    close(fd1[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, &ret, 0);
    exit(ret);
}