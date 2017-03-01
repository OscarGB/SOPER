/**
* @file ejercicio8.c
* @author Jose Ignacio Garcia, Óscar Gómez
* @date 26-02-2017
*/

#define COMMANDS 2
#define COMMANDSIZE 20

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char const *argv[]) {
    int flag = argc - 1;
    char path[20] = "/bin/";
    int status, i;
    char aux[100];
    char *prog[] = {aux, (char*) NULL};
    pid_t var;

    if(strcmp(argv[flag], "-l") == 0) { /*Asumimos que el flag del exec va a 
                                        ser el último argumento*/
        var = fork();

        for(i = 1; i < flag; i++){

            if(var == 0) { /*Si es un hijo, ejecuta el exec del flag*/
                strcat(path, argv[i]);
                execl(path, argv[i], NULL);
                perror("Error en l\n");
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

