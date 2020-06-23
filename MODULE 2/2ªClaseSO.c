// 2ª Clase SO

/*- LLAMADAS AL SISTEMA
	- Todo lo que acaba en "_t" es un tipo de archivo
	- Todo lo que empieza por "st_" es un campo(atributo) de la estructura stat
	- Macros para comprobar en st_mode

	Programa en c:*/

		int main(int argc, char *argv[]){
			// argc y argv
			//argc : Argument count; argv: Argument vector

			if(argc !=2){
				print("Error de argumentos");
				exit(1);
			}

			if(argv[1]==1)	// Incorrecto, estariamos comparando un puntero a char con un entero
			if(atoi(argv[1])==1))
			if(!strcmp(argv[1], "1"))	// También valido
				print("uno");
			else
				print("dos");

			struc stat atributos;

			// La funcion stat abre el fichero y copia sus valores en la estructura
			if(stat("datos.txt", &atributos)){	// La funcion stat devuelve un entero, si devuelve un <0 es porque ha habido un error
				// Si la llamada al sistema falla la salida "se redigiría" a perror
				perror("No se pudieron recuperar los atributos del fichero")
				exit(-1);
			}

			// Ahora queremos saber si ese fichero es regular
			if(S_ISREG(atributos.st_mode)){
				printf("El fichero es regular")
			}

			// Enlace simbolico:
				//"Acceso directo a un archivo que está en otro sitio"

			DIR *directorio;
			struct dirent *entrada;

			if(directorio = opendir("dir1")==NULL){
				perror("Error al abrir el directorio");
				exit(1);
			}

			while((entrada=readdir(directorio )) !=NULL){
				printf("Entrada: %s", entrada->d_name);	// El nombre de todos los ficheros que hay en un directorio
														// Entre ellos, tambien están contenido el directorio actual (.)
														// y el directorio padre (..)
			}
			// nombre de todos los archivos regulares contenidos en un directorio pasado como parametro			
		}

