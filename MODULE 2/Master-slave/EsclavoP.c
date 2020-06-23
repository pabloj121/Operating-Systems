
//ARCHIVO ersclavo.c
#include<math.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

int main(int argc, char *argv[]){
	int izq, dch, i, j;
	izq= atoi(argv[1]);
	dch= atoi(argv[2]);
	char cadena[20];
	int es_primo=1;


if(setvbuf(stdout,NULL,_IONBF,0)) {
	perror("\nError en setvbuf");
}

	for (i=izq; i<=dch; i++){
//sleep(random()%3);
///calculo largo de cp
		 printf("%10d\n", i);
		
	}
}