// ARCHIVO maestro.c
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

int main(int argc, char *argv[]){
	int e;
	if (argc != 3) {
		printf("\nmaster: faltan argumentos (valores del intervalo)");
		printf("\nPruebe: master <valor izquierdo> <valor derecho>, donde ambos valores son numeros enteros\n");
		exit(-1);
	}
	
	int aux1, aux2, num, n1;
	aux1=(atoi(argv[1])+atoi(argv[2]))/2;
	aux2=aux1+1;
	char cad[12];
	char cadenanum1[20];
	char cadenanum2[20];
	sprintf (cadenanum1, "%d", aux1);
	sprintf (cadenanum2, "%d", aux2);
	
	int i, num_hijo=1;
	
	int fd1[2];
	int fd2[2];
	pipe(fd1); pipe(fd2);
	pid_t PID;
	
	for (i=0; i<2; i++){
		if ( (PID= fork())<0) {
			perror("Error en fork");
			exit(1);
		}
		if (PID==0 && num_hijo==1){
			close(fd2[0]);
			close(fd2[1]);/// porque no quiero constar como escritor
			close(fd1[0]);//cierro lo que no uso
			dup2(fd1[1],STDOUT_FILENO);////////
			execlp("./esclavo", "esclavo", argv[1], cadenanum1, NULL);
			perror("Error en exec");
			exit(0);
		}
		else if (PID==0 && num_hijo==2){
			close(fd1[0]);
			///close(fd1[1]);
			close(fd2[0]);//cierro lo que no uso
			close(fd2[1]);
			dup2(fd1[1],STDOUT_FILENO);

			execlp("./esclavo", "esclavo", cadenanum2, argv[2], NULL);
			perror("Error en exec");
			exit(0);
		}
		num_hijo++;
	}
//padre

	close(fd1[1]); close(fd2[1]);//cierro lo que no uso

	//bucle mientras no fin de archivo fd1
	
	while ((      n1=read(fd1[0],cad , 11)    ) >0){
		cad[11]='\0';
		n1=atoi(cad);
		printf(" n1=%d, cad=%s",n1,cad);
	}
	printf ("al segundo while");
	while (( n1=read(fd2[0],cad , 11) >0)){
		printf(" n= %s",cad);
	}
	
	
	
}
