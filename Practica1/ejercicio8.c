/**
* @file ejercicio8.c
* @author Jose Ignacio Garcia, Óscar Gómez
* @date 26-02-2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char const *argv[]) {
	int flag, var, i, j;

	flag = argc - 1;

	if(strcmp(argv[flag], "-l") == 0) { /*Asumimos que el flag del exec va a 
										ser el último argumento*/
		var = fork();

		for(i = 1; i < flag; i++){
			if(var == 0) { /*Si es un hijo, ejecuta el exec del flag*/
				execl(argv[i], 0);
			}
			else if (var > 0){
				var = fork();
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
				execlp(argv[i], NULL);
			}
			else if (var > 0){
				var = fork();
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
				execv(argv[i], 0);
			}
			else if (var > 0){
				var = fork();
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
				execvp(argv[i], NULL);
			}
			else if (var > 0){
				var = fork();
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

	exit(EXIT_SUCCESS);
	return 0;
}