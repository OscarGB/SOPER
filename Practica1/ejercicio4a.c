/**
* Nombre: ejercicio4a.c
* Autores: Jose Ignacio Garcia, Óscar Gómez
* Fecha: 10-02-2017
* Grupo: 2202
* Pareja: 5
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define NUM_PROC 3 /*!< Numero de iteraciones*/


int main (void)
{
    int pid; /*id del proceso tras el fork*/
    int i; /*Contador de bucle*/
    
    for (i=0; i < NUM_PROC; i++){
        if ((pid=fork()) <0 ){
            printf("Error al emplear fork\n");
            exit(EXIT_FAILURE);
        }else if (pid ==0){
            
            sleep(1); /*Este sleep bloquea a los hijos para dar tiempo al padre
                        a salir. Sin él, había huérfanos que llegaban a la impresión antes
                        de la muerte del padre*/
            printf("HIJO %d / PADRE: %d\n", getpid(), getppid());
        }else{
            printf ("PADRE %d \n", getpid());
        }
    }
    exit(EXIT_SUCCESS);
}   