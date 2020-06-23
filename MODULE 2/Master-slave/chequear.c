#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>


int main(int argc, char* argv[]){
    int pid, ret, fd_error, bytesleidos;
    struct stat atributos;
    struct dirent *entrada;
    DIR *directorio;
    char dir[PATH_MAX], rutadirectorio[PATH_MAX], rutaerror[PATH_MAX];
    char nombre[NAME_MAX];
    char buffer_escritura[1024];
    int cauce[2];   

    if(pipe(cauce)){
        perror("No se puede abrir el pipe");
        exit(1);
    }   

    // ahora tenemos las entradas de la tabla de archivos abiertos "originales"
    // más los 2 pipes
    sprintf(dir, "/tmp/chequeos");

    if ((directorio = opendir(dir)) == NULL)
    {
        perror("Error al abrir el directorio\n"),
        exit(1);
    }

    umask(0); //via libre para dar permisos
    
    // creacion de archivo para redirigir salida de error
    if ((fd_error = open(, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU | S_IRWXG)) < 0)
    {
        perror("Error intentando crear fichero para salida de error");
        exit(1);
    }

    // recorremos cada entrada del directorio
    while ((entrada = readdir(directorio)) != NULL){
        sprintf(rutadirectorio, "%s/%s", dir, entrada->d_name);
        //strcat(entrada->d_name,dir);
        
        if (stat(rutadirectorio, &atributos) < 0){
            perror("Error al ejecutar stat\n");
            exit(1);
        }
        
        if (S_ISREG(atributos.st_mode)){
            //printf("%d\n", "%d\n", atributos.st_uid, atributos.st_gid);
            if ((pid = fork()) < 0){ // error
                perror("Error creando el segundo hijo\n");
                exit(1);
            }
            else if (pid == 0){ // hijo
                close(cauce[0]);// cierro lo que no uso

                if (dup2(cauce[1],STDOUT_FILENO) < 0)
                {
                    perror("Error intentando duplicar entrada de la tabla de archivos\n");
                    exit(1);
                }
                execlp(rutadirectorio, entrada->d_name, argv[1], NULL);
                perror("Error al hacer el exec\n");
                exit(1);
            }
            else{ //padre
                close(cauce[1]);

                /*if (dup2(STDOUT_FILENO, cauce[0]) < 0){
                    perror("Error intentando duplicar entrada de la tabla de archivos\n");
                    exit(1);
                }*/
                //read(int fd, void *buf, size_t count);
                while ((bytesleidos = read(cauce[0], buffer_escritura, 256 * sizeof(char))) > 0)
                {
                    printf("%s", buffer_escritura);
                }

                // esperamos a que acabe el hijo y chequeamos cómo finalizó
                wait(&ret);
                
                if(ret == EXIT_SUCCESS){
                    printf("El proceso hijo finalizó correctamente\n");
                }
                else if(ret == EXIT_FAILURE){
                    printf("El proceso hijo finalizó en condiciones de error\n");
                }
            }
            //wait(&ret);

            /*if (ret == EXIT_SUCCESS)
            {
                if ((pid = fork()) < 0)
                {
                    perror("Error creando segundo hijo\n");
                    exit(1);
                }
                else if (pid == 0)
                {
                    execlp("mountpoint", "mountpoint", NULL);
                    perror("Error en exec de mountpoint");
                    exit(1);
                }
                wait(NULL);
            }*/
        }
        printf("\n");
    }    
    
    close(cauce[0]);
    close(cauce[1]);
    exit(ret);
}