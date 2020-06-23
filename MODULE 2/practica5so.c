SESION 5 - SEÑALES

	kill es enviar una señal a un proceso
	kill -l : Nos dice el numero de procesos...? 
	sigterm es la señal que se envia a un proceso por ejemplo cuando hacemos Ctrl+C

	Las señales contienen: 
		- Array de bits de señales pendientes
		- Manejadores de señales
			-Ignorar
			- Finalizar
			- Finalizar + core (generando un archivo core: almacena la imagen de ese proceso para
			 que despues podamos depurarlo(que contenia pc, puntero de pila, variables...))
				sigkill significa Finalizar+core (devolviendo señal -9)
			- Parar (Ctrl+Z) / Reanudar
			- Manejador de señal -> funcion definida en el codigo del proceso
			Sigaction me va a permitir modificar la accion por proceso de una señal

		SIGSTOP Y SIGKILL no se puede modificar su comportamiento

	Un proceso confirma que tiene señales pendientes cuando pasa de modo kernel a modo usuario

	El que recibe señales tenemos que ejecutarlo en background
    