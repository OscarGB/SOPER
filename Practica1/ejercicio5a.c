/**
* @file ejercicio5a.c
* @author Jose Ignacio Garcia, Óscar Gómez
* @date 10-02-2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

#define NUM_PROC 3 /*!< Ńumero de iteraciones*/

int main (void)
{
	int pid;
	int i;
	int c;
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
			sleep(1);
			printf("HIJO %d / PADRE: %d\n", getpid(), getppid());
		}else{
			printf ("PADRE %d\n", getpid());
		}
	}
	wait(&c);
	exit(EXIT_SUCCESS);
}
