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
#include<string.h>

/*Llamadas al sistema

-open -> abrir un fichero
	devuelve un descriptor de fichero("apertura de un fichero")

	hay dos formas de llamar a open
	open("/ruta/al/fichero", ......(Modo de apertura))	// O_RDONLY,O_WRONLY, O_RDWR

	O_WRONLY | O_TRUNC | O_CREAT
	otrunc: trunca el fichero, borra todo el contenido
	ocreat: si no existe el fichero, lo crea
		solo tiene sentido si vamos a escribir
		siempre que pongamos el ocreat, tenemos que indicar tambien los permisos(por cojones 3 parámetros)

	Con 3 parametros:
		-> S_IRWX {U,G ú O}	// user, group or other
		-> S_I{R,W,X}{USR,GRP,OTH}
		-> 

-read -> Lee datos del fichero
	devuelve la cantidad de bytes leidos

	read(fd,buffer,30)
		fd: descriptor del fichero; 30: tamaño en bytes que queremos leer; buffer: vector donde se almacenará lo leído

-write -> Escribe en un fichero
	devuelve el nº de bytes escritos

	write(fd,buffer,bytes)
	La unica diferencia con respecto a read es que en éste buffer es donde estará la información que vamos a escribir

-close -> Cierra la apertura del fichero
	close(fd);


NOTA: en la mayoría de los casos, si hay un error, estas operaciones devolverán -1

--------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------

printf(".....1*", var1,var)
	1*: cadena de formato
		% indica que en esa posicion vamos a sustituirlo por el valor de una variable
			%s -> indica el tipo de variable
				d -> enteros
				f -> float
				s -> cadena de caracteres
				c -> caracter

-------------------------------------------------------------------------------------
ejemplo de main usando printf
-------------------------------------------------------------------------------------

int main(){
	int fd;
	fd=open("/home/user/datos.txt",O_RDONLY);
	char bloque[50];
	read(fd,bloque,50);
	printf("%s", bloque);
}
*/

//--------------------------------------------------------------//-----------------------
//ejemplo de main con llamadas al sistema
//-------------------------------------------------------------------------------------


int main(){
	int fd1, fd2, bytesleidos;
	char bloque[]="hola caracola como mola so\n";
	
	if((fd1=open("fich1",O_RDONLY))<0){
		perror("No se pudo abrir el fichero");
		exit(1);
	}

	// umask(0); con el 0 podemos dar todos los permisos que queramos
	if((fd2=open("fich2",O_WRONLY|O_TRUNC|O_CREAT, S_IRWXU|S_IRWXG))<0){
		perror("....");
		exit(1);
	}

	if((bytesleidos=read(fd1,bloque,512))<0){
		perror("Error al leer");
		exit(1);
	}

	if(write(fd2,bloque,512)<0){
		perror("Error al escribir");
	}

	close(fd1);
	close(fd2);
}
