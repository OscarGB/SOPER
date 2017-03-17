/**
* @file ejercicio3b.c
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


#define MAX_THREAD 100 /*!< Número máximo de threads a ejecutar*/
#define TRUE 1 /*!< Booleano (verdadero)*/
#define FALSE 0 /*!< Booleano (falso)*/

/**
 * Función que comprueba si un número es primo
 * @author Jose Ignacio Garcia, Óscar Gómez
 * @date 03-03-2017
 * @param int a, número a comprobar 
 * @return int, boolean, verdadero o falso
 */
int esPrimo(int a) {
    int i;

    for(i = 2; i < a/2; i++){ /*Sólo hasta a/2 para mejorar la eficiencia*/
        if((int) a % i == 0) {
            return FALSE;
        }
    }

    return TRUE;
}

/**
 * Función que calcula n números primos
 * @author Jose Ignacio Garcia, Óscar Gómez
 * @date 03-03-2017
 * @param void *n, número de primos a calcular
 */
void *calculaPrimo(void *n) {
    int i, numprimos;
    int *maxprimos;

    numprimos = 0;
    i = 0;

    maxprimos = (int*) n;

    while(numprimos < *maxprimos){
        if(esPrimo(i) == TRUE) { /*Comprobación de si es primo o no*/
            numprimos++;
        }
        i++;
    }

    
    pthread_exit(NULL);
}   

int main(int argc, char const *argv[]) {    
    int i, n, numprimos, primo;
    pthread_t t[MAX_THREAD]; /*Array de threads*/

    double timeTotal; 

    struct timeval start, end; /*Estructuras para calcular tiempos*/

    gettimeofday(&start, NULL); /*Inicio de la contabilización de tiempos*/

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

    gettimeofday(&end, NULL); /*Fin de la contabilización de tiempo*/

    timeTotal =  (double)((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)) / 1000000; /*Calculo del tiempo total*/

    printf("El programa ha tardado %lf segundos en calcular %d primos.\n", timeTotal, n);

    return 0;

}
