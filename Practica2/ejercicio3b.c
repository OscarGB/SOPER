/**
* @file ejercicio3a.c
* @author Jose Ignacio Gomez, Óscar Gómez
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


#define MAX_THREAD 100
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

void *calculaPrimo(void *n) {
	int i, numprimos;
	int *maxprimos;

	numprimos = 0;
	i = 0;

	maxprimos = (int*) n;

	while(numprimos < *maxprimos){
		if(esPrimo(i) == TRUE) {
			numprimos++;
		}
		i++;
	}

	
	pthread_exit(NULL);
}	

int main(int argc, char const *argv[]) {	
	int i, n, numprimos, primo;
	pthread_t t[MAX_THREAD];

	double timeTotal;

	struct timeval start, end;

  	gettimeofday(&start, NULL);

	if(argc < 2) {
		printf("Introduce el número de primos a calcular. \n");
		return -1;
	}

	n = atoi(argv[1]);

	for(i = 0; i < MAX_THREAD; i++) {
		pthread_create(&(t[i]), NULL, calculaPrimo, (void*) &n);
	}

	for(i = 0; i < MAX_THREAD; i++) {
		pthread_join(t[i], NULL);
	}

	gettimeofday(&end, NULL);

	timeTotal =  (double)((end.tv_sec * 1000000 + end.tv_usec)
		  - (start.tv_sec * 1000000 + start.tv_usec)) / 1000000;

	printf("El programa ha tardado %lf segundos en calcular %d primos.\n", timeTotal, n);

	return 0;

}