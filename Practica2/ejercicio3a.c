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
#include <time.h>
#include <math.h>
#include <sys/wait.h>
#include <sys/types.h>

double sqrt(double a);

#define NUM_HIJOS 100
#define TRUE 1
#define FALSE 0

int esPrimo(int a) {
	int i;

	for(i = 2; i < a; i++){
		if((int) a % i == 0) {
			return FALSE;
		}
	}

	return TRUE;
}	

int main(int argc, char const *argv[]) {	
	int pid, i, n, numprimos, primo;
	clock_t start, end;
	double time;

	start = clock();

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

	end = clock();

	time = (double) (end - start) / CLOCKS_PER_SEC;

	printf("El programa ha tardado %lf segundos en calcular %d primos.\n", time, n);

	return 0;
}