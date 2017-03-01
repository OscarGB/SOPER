/**
* @file ejercicio8.c
* @author Jose Ignacio Garcia, Óscar Gómez
* @date 26-02-2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

#define LECTURA 0
#define ESCRITURA 1

typedef enum {
	SUMA = 0, RESTA, PRODUCTO, COCIENTE,
} Operaciones;

int main() {
	pid_t pchild;
	int op1, op2, resultado, i; 
	int a[2], b[2], pipe_status, nbytes; /*El pipe a va de padre a hijo*/
	char *string = "20,40\n";
	char readbuffer[200], childbuffer[200];
	char *tok1 = NULL, *tok2 = NULL;
	int status;

	/*pipe_status = pipe(a);
	if(pipe_status == -1) {
		perror("Error de pipe a\n");
		exit(EXIT_FAILURE);	
	}

	pipe_status = pipe(b);
	if(pipe_status == -1) {
		perror("Error de pipe b\n");
		exit(EXIT_FAILURE);	
	}

	if((pchild = fork()) == -1) {
		perror("fork error");
		exit(EXIT_FAILURE);
	}*/

	for(i = 0; i < 4; i++){
		pipe_status = pipe(a);
		if(pipe_status == -1) {
			perror("Error de pipe a\n");
			exit(EXIT_FAILURE);	
		}

		pipe_status = pipe(b);
		if(pipe_status == -1) {
			perror("Error de pipe b\n");
			exit(EXIT_FAILURE);	
		}

		if((pchild = fork()) == -1) {
			perror("fork error");
			exit(EXIT_FAILURE);
		}
		if(pchild > 0) {
			close(a[0]); /*Para escribir*/
			close(b[1]); /*Para leer*/
			write(a[1], string, strlen(string));
			wait(&status);
			strcpy(readbuffer, "");
			nbytes = read(b[0], readbuffer, sizeof(readbuffer));
			printf("%s", readbuffer);
			if(i < 3){
				//pchild = fork();
			}
		}
		if(pchild == 0){
			close(a[1]); /*Para leer*/
			close(b[0]); /*Para escribir*/
			nbytes = read(a[0], readbuffer, sizeof(readbuffer));

/*printf("read: %s\n", readbuffer);*/

			tok1 = strtok(readbuffer, ", ");
			tok2 = strtok(NULL, ", ");

			strcpy(childbuffer, "");


			op1 = atoi(tok1);
			op2 = atoi(tok2);

			if(i == SUMA){
				resultado = op1 + op2;
				sprintf(childbuffer, "Datos enviados a través de la tubería por el proceso PID= %d\nOperando 1: %d. Operando 2: %d. Suma: %d\n", getpid(), op1, op2, resultado);
			}
			else if(i == RESTA){
				resultado = op1 - op2;

				sprintf(childbuffer, "Datos enviados a través de la tubería por el proceso PID= %d\nOperando 1: %d. Operando 2: %d. Resta: %d\n", getpid(), op1, op2, resultado);
			}
			else if(i == PRODUCTO){
				resultado = op1 * op2;

				sprintf(childbuffer, "Datos enviados a través de la tubería por el proceso PID= %d\nOperando 1: %d. Operando 2: %d. Producto: %d\n", getpid(), op1, op2, resultado);
			}
			else if(i == COCIENTE){
				resultado = op1 / op2;

				sprintf(childbuffer, "Datos enviados a través de la tubería por el proceso PID= %d\nOperando 1: %d. Operando 2: %d. Cociente: %d\n", getpid(), op1, op2, resultado);
			}
			write(b[1], childbuffer, strlen(childbuffer));
			exit(EXIT_SUCCESS);
		}
	}
		
	exit(EXIT_SUCCESS);
	return 0;
}