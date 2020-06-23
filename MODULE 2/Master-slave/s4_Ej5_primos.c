/*
	esclavo:		Realiza la tarea encomendada por el maestro.
	maestro:		Reparte la tarea y recibe los resultados.

	Muestra los números primos que hay en el intervalo [minimo, maximo[
*/
/* Bibliotecas ****************************************************************/

#include <stdio.h>	// printf, fprintf, stdout, STDOUT_FILENO.
#include <stdlib.h>	// atoi
#include <math.h>		// sqrt
#include <unistd.h>	// write
/* Programa Principal *********************************************************/
int main(int argc, char *argv[]){
	if(argc <3){
		fprintf(stdout, "\n Sintaxis: %s a b ", argv[0]);
		printf("\n a  --> Extremo inferior del intervalo.");
		printf("\n b  --> Extremo superior del intervalo.");
	}
	else{
		int minimo = atoi(argv[1]);
		int maximo = atoi(argv[2]);
		if(minimo > maximo){	int swap = minimo;	minimo=maximo;		maximo=swap;}

		int numero_de_enteros = maximo-minimo;		// Cantidad de números a analizar
		int numero[numero_de_enteros+1];				// Array que contendrá a los números a analizar
//		float limite = sqrt(maximo);					// Limite de enteros divisores.
		float limite = maximo;					// Limite de enteros divisores.
//		for(int i=0; i<=numero_de_enteros; i++){
//			numero[i]=minimo+i;	}	// Rellenando el Array, maximo inclusive
		for(int i=0; i< numero_de_enteros; i++){
			numero[i]=minimo+i;	}	// Rellenando el Array, maximo no inclusive.
		for(int i=2; i< limite; i++){					// Divisores.
			for(int j=0; j<=numero_de_enteros; j++){
				if(numero[j]!= 0 &&		// Condiciones:	El número debe ser no 0
					numero[j]!= i &&		//						El número debe ser distindo al divisor.
					numero[j]%i == 0)		//						Si el resto es 0, es un número compuesto.
					{numero[j] = 0;}		//		Marcando que el número es compuesto.
			}
		}
//		printf("\n [%d, %d[ --> ", minimo, maximo);		// Estédica de salida.
		for(int i=0; i<numero_de_enteros; i++){	// Recorriendo el array
//			if(numero[i]!=0){fprintf(stdout," %d", numero[i] );}	// Mostrando los números primos
			if(numero[i]!=0){ write(STDOUT_FILENO, &numero[i], sizeof(int) );}	// Mostrando los números primos
//			if(numero[i]!=0){ fprintf(stdout, "%d", numero[i] );}	// Mostrando los números primos
//			if(numero[i]!=0){ fprintf(stderr, "%d", numero[i]);}	// Mostrando los números primos
		}
	}
	printf("\n");							// Estética de salida.
	return 0;

}
