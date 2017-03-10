/**
* @file ejercicio3a.c
* @author Jose Ignacio Garcia, Óscar Gómez
* @date 03-03-2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <math.h>
#include <sys/wait.h>
#include <sys/types.h>

#define NUM_HIJOS 100
#define TRUE 1
#define FALSE 0

int esPrimo(int a) {
	int i;

	for(i = 2; i < a/2; i++){
		if((int) a % i == 0) {
			return FALSE;
		}
	}

	return TRUE;
}	

int main(int argc, char const *argv[]) {	
	int pid, i, n, numprimos, primo;
	
	double timeTotal;

	struct timeval start, end;

  	gettimeofday(&start, NULL);


	if(argc < 2) {
		printf("Introduce el número de primos a calcular. \n");
		return -1;
	}

	n = atoi(argv[1]);

	for (i = 0; i < NUM_HIJOS; i++) {
		pid = fork();

		if(pid == 0) {
			/*calcular primos*/
			primo = 2;
			numprimos = 0;
			while(numprimos < n){
				if(esPrimo(primo) == TRUE){
					primo++;
					numprimos++;

				}
				else {
					primo++;
				}
			}
			exit(EXIT_SUCCESS);
		}
		else if(pid < 0) { 	
			printf("Error en el fork %d.\n", i);
			exit(EXIT_FAILURE);
		}
	}

	while(wait(NULL) > 0);

	gettimeofday(&end, NULL);

	timeTotal =  (double)((end.tv_sec * 1000000 + end.tv_usec)
		  - (start.tv_sec * 1000000 + start.tv_usec)) / 1000000;

	printf("El programa ha tardado %lf segundos en calcular %d primos.\n", timeTotal, n);

	return 0;
}