/**
* @file ejercicio6.c
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

int main() {
	char *string;
	int estado;

	string = (char *)malloc(80*sizeof(char));
	if(!string) return -1;

	strcpy(string, "Vacio");

	if(fork() == 0){
		scanf("%s", string);

		printf("La cadena en el hijo vale: %s\n", string);
	}
	else {
		wait(&estado);
		printf("La cadena en el padre vale: %s\n", string);
	}

	free(string);

	exit(EXIT_SUCCESS);

	return 0;
}