/**
* Nombre: ejercicio8.c
* Autores: Jose Ignacio Garcia, Óscar Gómez
* Fecha: 27-02-2017
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

int main(int argc, char const *argv[]) {
    int flag = argc - 1; /*Indica la posición del flag dentro de *argv[]*/
    char path[20] = "/bin/"; /*Cadena donde almacenaremos el path del comando*/
    int status, i; 
    char aux[100]; /*Cadena de caracteres que empleamos como primer elemento
                    del array prog[]*/
    char *prog[] = {aux, (char*) NULL}; /*Array de cadenas donde almacenaremos
                                        los argumentos de las funciones execv y execvp*/
    pid_t var; /*id del proceso tras el fork*/

    if(strcmp(argv[flag], "-l") == 0) { /*Asumimos que el flag del exec va a 
                                        ser el último argumento*/
        var = fork();

        for(i = 1; i < flag; i++){

            if(var == 0) { /*Si es un hijo, ejecuta el exec del flag*/
                strcat(path, argv[i]); /*Rellenamos el path*/
                execl(path, argv[i], NULL);
                perror("Error en l\n");
                exit(EXIT_FAILURE);
            }
            else if (var > 0){
                wait(&status); /*Esperamos a que termine*/
                if(i < flag - 1){
                    var = fork();
                }
            }
            else {
                printf("Error haciendo fork\n");
                exit(EXIT_FAILURE);
            }
        }

    }

    else if(strcmp(argv[flag], "-lp") == 0) { /*Asumimos que el flag del exec va a 
                                        ser el último argumento*/
        var = fork();

        for(i = 1; i < flag; i++){
            if(var == 0) { /*Si es un hijo, ejecuta el exec del flag*/
                execlp(argv[i], argv[i], (char *)NULL);
                perror("Error en lp\n");
                exit(EXIT_FAILURE);
            }
            else if (var > 0){
                wait(&status);
                if(i < flag - 1){
                    var = fork();
                }
            }
            else {
                printf("Error haciendo fork\n");
                exit(EXIT_FAILURE);
            }
        }

    }

    else if(strcmp(argv[flag], "-v") == 0) { /*Asumimos que el flag del exec va a 
                                        ser el último argumento*/

        var = fork();

        for(i = 1; i < flag; i++){
            if(var == 0) { /*Si es un hijo, ejecuta el exec del flag*/
                strcat(path, argv[i]);
                strcpy(prog[0], path);
                execv(path, prog);
                perror("Error en v\n");
                exit(EXIT_FAILURE);
            }
            else if (var > 0){
                wait(&status);
                if (i < flag-1){
                    var = fork();
                }
            }
            else {
                printf("Error haciendo fork\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    else if(strcmp(argv[flag], "-vp") == 0) { /*Asumimos que el flag del exec va a 
                                        ser el último argumento*/

        var = fork();

        for(i = 1; i < flag; i++){
            if(var == 0) { /*Si es un hijo, ejecuta el exec del flag*/
                strcpy(prog[0], argv[i]);
                execvp(argv[i], prog);
                perror("Error en v\n");
                exit(EXIT_FAILURE);
            }
            else if (var > 0){
                wait(&status);
                if (i < flag-1){
                    var = fork();
                }
            }
            else {
                printf("Error haciendo fork\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    else {
        printf("No se ha reconocido la entrada. Pruebe con: ./<ejecutable> [orden] ... [flag]");
        exit(EXIT_FAILURE);
        return -1;
    }
    wait(&status);
    exit(EXIT_SUCCESS);
    return 0;

}

