/**
* @file ejercicio4.c
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

#define MAX_LINEA 100000 /*!<Tamaño máximo de la línea a imprimir*/

typedef struct _Hilo Hilo; /*!<Definición de la estructura Hilo*/

struct _Hilo
{
	Hilo *otro; /*!<Estructura del otro hilo*/
	int progreso; /*!<Progreso del calculo*/
	int numero; /*!<Número del hilo*/
	int mul; /*!<Multiplicador aplicado a el hilo*/
	pthread_t p; /*!<El hilo*/
	int **matriz; /*!<matriz a calcular*/
	int *dim; /*!<Dimension de la matriz*/
};

/**
* Función utilizada por los hilos, multiplica una matriz por un multiplicador dado
* @param void *hilo, el hilo que se está ejecutando, incluye todos los datos necesarios
*/
void *multiplica(void *hilo){
	Hilo *h = (Hilo *)hilo;
	int **mat = (int **) h->matriz;
	int i, j; /*bucles*/
	char linea[MAX_LINEA] = ""; /*Linea a imprimir*/
	char aux[MAX_LINEA] = ""; /*String auxiliar para concatenación*/
	for(i = 0; i < (*(h->dim)); i++){
		sprintf(linea, "Hilo %d multiplicando fila %d resultado:", h->numero , i);
		for(j = 0; j < (*(h->dim)); j++){
			sprintf(aux, " %d", ((mat)[i][j]*(h->mul))); /*Multiplicación de las componentes*/
			strcat(linea, aux);
		}
		h->progreso++;
		sprintf(aux, " - el Hilo %d va por la fila %d\n", h->otro->numero, h->otro->progreso); /*Datos del otro hilo*/
		strcat(linea, aux);
		printf("%s", linea);
		sleep(1); /*Espera para comprobar el resultado*/
	}
} 

int main(){
	Hilo *h1 = NULL;
	Hilo *h2 = NULL;
	int dim; /*Dimensión de la matriz*/
	int i, j; /*bucles*/
	int **matriz1; /*Matriz para hilo 1*/
	int **matriz2; /*Matriz para hilo 2*/

	printf("Introduzca dimension de la matriz cuadrada:\n");
	scanf("%d", &dim);

	if(dim < 0 || dim > 4){
		printf("La dimensión no puede ser superior a 4 o menor que 0.\n");
		return EXIT_SUCCESS;
	}


	/*Creación de los hilos*/
	h1 = (Hilo *)malloc(sizeof(Hilo));
	if(!h1) return 1;
	h2 = (Hilo *)malloc(sizeof(Hilo));
	if(!h2){
		free(h1);
		return 1;
	}

	/*Código para primera matriz*/
	matriz1 = (int **)malloc(sizeof(int *) * dim);
	if(!matriz1){
		free(h1);
		free(h2);
	}

	printf("Introduzca matriz 1:\n");

	for(i = 0; i < dim; i++){
		matriz1[i] = (int *)malloc(sizeof(int) * dim);
		if(!matriz1[i]){
			for(j = 0; j < i; j++){
				free(matriz1[j]);
			}
			free(h1);
			free(h2);
			free(matriz1);
			break;
		}
		for(j = 0; j < dim; j++){
			scanf("%d", &(matriz1[i][j]));
		}
	}
	/*Fin código para primera matriz*/

	/*Código para segunda matriz*/
	matriz2 = (int **)malloc(sizeof(int *) * dim);
	if(!matriz1){
		free(h1);
		free(h2);
	}

	printf("Introduzca matriz 2:\n");

	for(i = 0; i < dim; i++){
		matriz2[i] = (int *)malloc(sizeof(int) * dim);
		if(!matriz2[i]){
			for(j = 0; j < i; j++){
				free(matriz2[j]);
			}
			for(j = 0; j < dim; j++){
				free(matriz1[j]);
			}
			free(h1);
			free(h2);
			free(matriz2);
			free(matriz1);
			break;
		}
		for(j = 0; j < dim; j++){
			scanf("%d", &(matriz2[i][j]));
		}
	}
	/*Fin código para segunda matriz*/

	/*Asignación datos de los hilos a sus estructuras*/
	h2->otro = h1;
	h1->otro = h2;
	h1->progreso = 0;
	h2->progreso = 0;
	h1->numero = 1;
	h2->numero = 2;
	h1->matriz = matriz1;
	h2->matriz = matriz2;
	h1->dim = &dim;
	h2->dim = &dim;

	printf("Introduzca multiplicador 1: \n");
	scanf("%d", &(h1->mul));

	printf("Introduzca multiplicador 2: \n");
	scanf("%d", &(h2->mul));
	/*Fin asignación*/

	/*Creación hilos*/
	pthread_create(&(h1->p), NULL, multiplica, (void*)h1);
	pthread_create(&(h2->p), NULL, multiplica, (void*)h2);

	/*Unión de los hilos con el actual*/
	pthread_join(h1->p, NULL);
	pthread_join(h2->p, NULL);

	/*Liberación de memoria*/
	for(j = 0; j < dim; j++){
		free(matriz1[j]);
		free(matriz2[j]);
	}
	free(h1);
	free(h2);
	free(matriz2);
	free(matriz1);

	return EXIT_SUCCESS;


}