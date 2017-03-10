/**
* @file ejercicio6.c
* @author Jose Ignacio Gómez, Óscar Gómez
* @date 10-03-2017
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

void *multilica(void **mat, void *dim,void *estehilo, void *otrohilo, void *numhilo, void *mult){
	int i, j;
	for(i = 0; i < (int)(*(dim)); i++){
		printf("Hilo %d multiplicando fila %d resultado:", (int)(*numhilo), i);
		for(j = 0; j (int)(*(dim)); j++){
			printf(" %d", (int)(mat[i][j]*(*mult)));
		}
		(int)(*estehilo) = (int)(*estehilo) + 1;
		if((int)(*numhilo) == 1){
			printf(" - el Hilo 2 va por la fila %d\n", (int)(*otrohilo));
		}
		sleep(1);
	}
} 

int main(){
	int dim, mul1, mul2, i, hilo1 = 0, hilo2 = 0;
	pthread_t p1, p2;
	int matriz[4][4];
	int a = 1; b = 2;

	printf("Introduzca dimension de la matriz cuadrada:\n");
	scanf("%d", &dim);

	if(dim < 0 || dim > 4){
		printf("La dimensión no puede ser superior a 4 o menor que 0.\n");
		return EXIT_SUCCES;
	}

	printf("Introduzca multiplicador 1: \n");
	scanf("%d", &mul1);

	printf("Introduzca multiplicador 2: \n");
	scanf("%d", &mul2);

	pthread_create(&p1, NULL, multiplica, (void**) matriz, (void*)dim, (void*)hilo1, (void*)hilo2, (void*)a, (void*)mul1);
	pthread_create(&p2, NULL, multiplica, (void**) matriz, (void*)dim, (void*)hilo2, (void*)hilo1, (void*)b, (void*)mul2);

	pthread_join(p1, NULL);
	pthread_join(p2, NULL);

	return 0;


}