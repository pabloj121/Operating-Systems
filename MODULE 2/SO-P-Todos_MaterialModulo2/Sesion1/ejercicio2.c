/* Ejercicio 2 - Sesion 1 - SO
	*/


#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<errno.h>


int main(int argc, char *argv[])
{
int fdin, fdout;

/* Numero correcto de parametros, comprobamos que no da error*/
if(argc==2){
	if(fdin = open(argv[1], O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR))<0)
	{
		printf("\nError %d en open", errno);
		perror("\nError en open");
		exit(EXIT_FAILURE);
	}
}
else{
	filein = STDIN_FILENO;
}

/*if((fdin = open("archivo", O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR))<0){
	printf("\nError %d en open", errno);
	perror("\nError en open");
	exit(EXIT_FAILURE);
}*/


if(fdout = write(fdin, "salida.txt",80)){
	fdout = write(fdin
	while(fdout = write(fdin, "salida.txt",80)){
}
