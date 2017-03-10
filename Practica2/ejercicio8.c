/**
* Nombre: ejercicio8.c
* Autores: Jose Ignacio Gomez, Óscar Gómez
* Fecha: 10-03-2017
* Grupo: 2202
* Pareja: 5
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

#define NUM_PROC 4 /*!< Ńumero de iteraciones*/

int main() {
	int pid, pid_root; /*id del proceso tras el fork*/
    int i; /*Contador de bucle*/
    int status; /*int de estado para pasar al wait como argumento*/
    
	pid_root = getpid();

    if ((pid=fork()) <0 ){
        printf("Error haciendo fork\n");
        exit(EXIT_FAILURE);
    }
    for (i=0; i < NUM_PROC; i++){
        if (pid == 0){
            if ((pid=fork()) <0 ){
                printf("Error haciendo fork\n");
                exit(EXIT_FAILURE);
            }
            if (i == NUM_PROC - 1){
            	status = kill(pid_root, SIGUSR1);
            }
            printf("HIJO %d / PADRE: %d\n", getpid(), getppid());
        }else{
        	pause();
            printf ("PADRE %d\n", getpid());
        }
    }
    wait(&status);
    exit(EXIT_SUCCESS);

	return 0;
}