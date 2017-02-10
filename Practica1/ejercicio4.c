/**
* @file ejercicio4.c
* @author Jose Ignacio Garcia, Óscar Gómez
* @date 10-02-2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#define NUM_PROC 3

int main (void)
{
	int pid;
	int i;
	int c;
	for (i=0; i < NUM_PROC; i++){
		if ((pid=fork()) <0 ){
			printf("Error al emplear fork\n");
			exit(EXIT_FAILURE);
		}else if (pid ==0){
			printf("HIJO %d / PADRE: %d\n", getpid(), getppid());
		}else{
			printf ("PADRE %d \n", getpid());
		}
	}
	c = getchar();
	exit(EXIT_SUCCESS);

}	