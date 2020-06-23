 /*Apuntes fork

¿que diferencia hay entre un proceso padre y un hijo?
	- el PID
	- lo que devuelve la función fork... un 0 en el hijo y el PID 	del 	hijo en el padre.
*/
#include<math.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>


int main(){
	int pid[15];
	//pid = fork();
	//printf("%d", pid);

	/*if(pid != 0)
		printf("Papa\n");
	else
		printf("Nini\n");*/

	//crea 5 hijos y cada hijo muestra su pid por pantalla
	for (int i = 0; i < 15 && pid; ++i){
		pid = fork();
		if (pid != 0){
			printf("El pid del hijo es ", pid.getpid());
		}
		wait
	}	
}	