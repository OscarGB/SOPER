/**
* Nombre: ejercicio6.c
* Autores: Jose Ignacio Garcia, Óscar Gómez
* Fecha: 25-02-2017
* Grupo: 2202
* Pareja: 5
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void) {
    char *string; /*Cadena en la que almacenaremos los datos leídos*/
    int estado; /*int de estado para pasar al wait como argumento*/
    int pid; /*id del proceso tras el fork*/

    string = (char *)malloc(80*sizeof(char)); /*Reservamos memoria para los datos leidos*/
    if(!string) return -1;

    strcpy(string, "Vacio"); /*Inicilaizamos la cadena para que 
                            el padre muestre un contenido no vacío*/

    pid = fork();

    if(pid == 0){
        scanf("%s", string);

        printf("La cadena en el hijo vale: %s\n", string);
    }
    else if (pid > 0){
        wait(&estado);
        printf("La cadena en el padre vale: %s\n", string);
    }
    else {
        printf("Error haciendo fork\n");
        exit(EXIT_FAILURE);
    }

    free(string);

    exit(EXIT_SUCCESS);
}