//Llamadas al Sistema - Subsistema Procesos

//exec: sustituye el programa que se esta ejecutando ejecuta un
/*programa que está en nuestra lista de archivos

Ejemplo:

int main(){
	exec...// si exec se ejecutara bien, no haría el printf
	printf("...\n");
	

	execl es mas sencillo de usar, puede venir acompañado de una p(PATH)
	path contiene una lista de donde están los ejecutables

	execlp busca en las rutas del sistema

	la "l" es cómo le vamos a pasar los argumentos

	// aqui la p no sería necesaria ya que ejecutariamos un programa
	// "nuestro", no uno perteneciente al sistema
	excelp(nombre del programa,arvg[0]("./nombre"), argv[1], (argv[2]), NULL);
	printf("aquí\n");

// programa que ejecuta un ls y espera a que termine
	int pid;	//pid_t es como un int ... ~~parecido
	/*FORK si padre devuelve pid del hijo
	si hijo devuelve un 0(En la variable del hijo se pone un 0)*/
	/*if ((pid = fork()) < 0){
		perror("Error"), exit(1);
	}
	else if(pid == 0){
		execlp("ls", "ls", NULL);
		perror("Error"), exit(1);
	}
	wait(NULL);
	
	/*  int est;
		wait(&est);
	*/

//}
#include<unistd.h> 
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include<stdio.h>
#include<errno.h>
#include<dirent.h>
#include<string.h>

int veces = 0;
void manejador(int n){
	printf("Bienvenido a TFormación online\n");
	veces++;
}

int main(){
	// ---------------------------------------------------------------------------
	// PRIMERA PARTE	
	// ---------------------------------------------------------------------------

	//struct sigaction s;
	//s.sa_handler = manejador;

	/*if(sigaction(SIGINT, &s, NULL) < 0){
		perror("Error"), exit(1);
	}
	while(veces < 5){
		sleep(1);
	}*/

	//pipe o fifos(ambos cauces)
	//pipes : cauces sin nombre
	//fifos: cauces con nombre

	//queremos que el padre comunique con un hijo o un hijo
	// con un padre

	// 1- Padre crea cauce
	// 2- Crea el hijo
	// Nota- Entre padre e hijo solo se diferencian el valor que devuelve fork y el pid
	// 3- 

	char c;
	pid_t pid;
	int fd[2];
	int bytes;

	if(pipe(fd) < 0)
		perror("Error\n");

	if((pid=fork()) < 0){
		perror("Error"), exit(1);
	}
	else if(pid == 0){//hijo
		close(fd[1]);
		if(bytes = read(fd[0], &c,1) < 0)
			perror("Error"), exit(1);
		printf("%c\n",c );
	}
	else{//padre
		close(fd[0]);
		c = 97;
		if(write(fd[1], &c, sizeof(char)) <0)
			perror("Error"), exit(1);
	}
	wait(NULL);
	close(fd[0]);
	
	if(write(fd[],,bytes)){
		
	}
}