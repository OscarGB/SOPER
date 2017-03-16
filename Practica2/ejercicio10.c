/**
* @file ejercicio10.c
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

#define PALABRA 10
#define NUM_PALABRAS 13

/**
* Función utilizada para obtener un número aleatorio para ver que palabra imprime
* @return int
*/
int randn(){
	int ret;
	double aux;
	aux = rand();
	aux = aux/RAND_MAX;
	aux = aux * (NUM_PALABRAS);
	ret = (int)aux;
	if(ret >= NUM_PALABRAS){
		ret = NUM_PALABRAS - 1;
	}
	return ret;
}

int main(){
	char frase[NUM_PALABRAS][PALABRA] = {"EL", "PROCESO", "A", "ESCRIBE", "EN", "UN", "FICHERO", "HASTA", "QUE", "LEE", "LA", "CADENA", "FIN"};
	int i, status;
	int imprime; /*Palabra a imprimir*/
	sigset_t set, oset, set1;
	int pid; /*Pid del hijo*/
	FILE* f = NULL;
	char *fichero = "ejercicio10.log";
	int palabrasleidas = 0; /*Número de palabras leidas por el proceso B*/
	char aux[PALABRA]; /*String auxiliar*/
	int flagalive; /*flag que comprueba si el proceso A sigue vivio*/

	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	sigemptyset(&set1);
	sigaddset(&set1, SIGUSR2);

	srand(time(NULL));

	fclose(fopen(fichero, "w")); /*vaciado del fichero*/

	pid = fork();
	if(pid < 0){
		printf("Error en el fork\n");
	}
	while(1){
		if(pid != 0){ /*Proceso B*/
			sleep(5);

			/*Esperar al hijo sin bliquear al padre*/
			if(waitpid(pid, &status, WNOHANG) <= 0){
				if(WIFEXITED(status)){
					/*Paramos el hijo*/
					kill(pid, SIGUSR1);
					/*Esperamos a que el hijo termine su seccion critica*/
					sigsuspend(&set1);
					flagalive = 1;
				}
			}

			f = fopen(fichero, "r");
			if(f == NULL){
				printf("Error al abrir el archivo\n");
				return EXIT_FAILURE;
			}

			while(fscanf(f, "%s", aux) != EOF){
				palabrasleidas++;
				if(palabrasleidas == 50){
					fclose(f);
					kill(pid, SIGKILL);
					return EXIT_SUCCESS;
				}
				/*comprobamos que no haya un FIN*/
				if(strcmp(aux, "FIN") == 0){
					flagalive = 0;
				}
			}

			fclose(f);

			/*Vaciado de fichero*/
			fclose(fopen(fichero, "w"));

			srand(time(NULL));

			if(flagalive == 1){
				/*Reactivación del hijo*/
				kill(pid, SIGUSR1);
			}
			else{
				pid = fork();
				if(pid < 0){
					printf("Error en el fork\n");
				}
			}

		}
		else{ /*Proceso A*/
			/*Seccion critica*/
			sigprocmask(SIG_BLOCK, &set, &oset);
			f = fopen(fichero, "a");
			if(f == NULL){
				printf("Error al abrir el archivo\n");
				return EXIT_FAILURE;
			}
			imprime = randn();
			fprintf(f, "%s\n", frase[imprime]);
			fclose(f);

			if(sigpending(&oset) == SIGUSR1){
				kill(getppid(), SIGUSR2);
				sigsuspend(&set);
			}

			if(imprime == (NUM_PALABRAS - 1)){
				exit(EXIT_SUCCESS);
			}
		}
	}


	return EXIT_SUCCESS;
}