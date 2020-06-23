// programa maestro.c

int main(int argc, char *argv[]){
	// argv[1] limite inferior
	// argv[2] limite superior
	int lim_inf = argv[1];
	int lim_sup = argv[2];
	int fd1[2],fd2[2];
	pid_t PID;
	pipe(fd1);
	pipe(fd2);
	
	//primer hijo
	if((PID=fork())==0){
		int numero = lim_inf;
		while(numero <= lim_sup /2){
			int a = 0;
			for (int i = 0; i < numero; ++i){
				if(numero%i==0)
					a++;
			}
			close(fd1[0]);
			close(STDOUT_FILENO);
			dup(fd1[1]);
			// Meter numero en el primer cauce
		}
	}//segundo hijo
	else if ((PID = fork())==0){
		int numero = lim_sup/2;
		while(numero <= lim_sup){
			int a = 0;
			for (int i = 0; i <= numero; ++i){
				if(numero%i==0)
					a++;
			}
			// Meter numero en el primer cauce
			close(fd1[0]);
			close(STDOUT_FILENO);
			dup(fd1[1]);
		}
	}
	// cerrados ambos cauces para escritura para que una operacion como la siguiente de fin de archivo
	// si el proceso padre lo tiene abierto, no se desbloquearía nunca
	while((n=read(fd1[0],,) > 0){
		mostrar en pantalla el numero leido
	}
	// ahora hacemos lo mismo para el segundo cauce
	while((n=read(fd2[0],,) > 0){
		mostrar en pantalla el numero leido
	}
}