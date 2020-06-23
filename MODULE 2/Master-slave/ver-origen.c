// ejercicio ver-origen.c
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
    int fd1[2];   

    if(pipe(fd1)){
        perror("No se puede abrir el pipe");
        exit(1);
    }   

    // ahora tenemos las entradas de la tabla de archivos abiertos "originales"
    // más los 2 pipes
    if((pid1 = fork) < 0){
        perror("Error creando primer hijo");
        exit(1);
    }
    else if(pid1 == 0){ // ls -ld ruta
       // redirigimos la salida a la entrada del segundo
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