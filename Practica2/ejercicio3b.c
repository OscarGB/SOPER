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


#define MAX_THREAD 100
#define TRUE 1
#define FALSE 0

void *calculaPrimo(void *n) {
	int i;
	int *a;

	a = (int*) n;

	for(i = 2; i < *a/2; i++){
		if((int) *a % i == 0) {
			pthread_exit(NULL);
			//return (void *) FALSE;
		}
	}

	pthread_exit(NULL);
	//return (void *)TRUE;
}	

int main(int argc, char const *argv[]) {	
	int i, n, numprimos, primo;
	pthread_t t[MAX_THREAD];
	clock_t start, end;
	double time;

	start = clock();

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

	end = clock();

	time = (double) (end - start) / CLOCKS_PER_SEC;

	printf("El programa ha tardado %lf segundos en calcular %d primos.\n", time, n);

	return 0;

}