/**
* Nombre: ejercicio8.c
* Autores: Jose Ignacio Gomez, Óscar Gómez
* Fecha: 10-03-2017
* Grupo: 2202
* Pareja: 5
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

#define NUM_PROC 4 /*!< Ńumero de iteraciones*/

int son_pid;
int root_pid;
int status;

int main() {
	int pid, pid_root; /*id del proceso tras el fork*/
    int i; /*Contador de bucle*/
    //int status; /*int de estado para pasar al wait como argumento*/
    int vueltas = -1;
    int v = 3; /** A BORRAR **/
    int padre = 0; /*1 si el proceso tiene hijos, 0 si no*/
    int son1_pid, last_son_pid;
    
	root_pid = getpid();
	printf("Root es %d | %d\n", root_pid, getpid());

	void manejador_USR1();
    void manejador_TERM();

    if ((pid=fork()) <0 ){
        printf("Error haciendo fork\n");
        exit(EXIT_FAILURE);
    }
    
    for(i = 0; i < NUM_PROC ; i++) { /*Generamos el árbol de procesos*/
    	//printf("PID: %d\n", pid);
    	if(pid == 0){
    		if ((pid=fork()) <0 ){
                printf("Error haciendo fork\n");
                exit(EXIT_FAILURE);
            }
            //printf("Proceso hijo: %d\n", getpid());
            if(i == NUM_PROC -1 && pid == 0){
            	//printf("Hola, i: %d\n", i);
            	son_pid = root_pid;
            	sleep(5);
            	kill(son_pid, SIGUSR1);
            	break;
            }
    	}
    	else {
    		printf("Proceso padre: %d | Hijo: %d\n", getpid(), pid);
    		padre = 1;
    		son_pid = pid;
    		break;
    	}
    }
    printf("Proceso %d\n", getpid());	

    while(vueltas < v){
        if(getpid() == root_pid) {
            vueltas++;
            printf("VUELTAS: %d\n", vueltas);
        }
		if(padre == 1){
			//printf("Proceso %d es padre y su hijo es %d\n", getpid(), son_pid);
    		if(signal(SIGUSR1, manejador_USR1) == SIG_ERR){
	    		perror("signal");
	    		exit(EXIT_FAILURE);
			}
    		pause(); /*Los padres se quedan esperando la llegada de una señal*/

    	}
    	else {
    		son_pid = root_pid;
    		//printf("Proceso %d es el último hijo, y el root es %d\n", getpid(), root_pid);
    		if(signal(SIGUSR1, manejador_USR1) == SIG_ERR){
	    		perror("signal");
	    		exit(EXIT_FAILURE);
			}
    		pause();
    		
    	}

    } /*Fin de bucle*/

    /*Ahora el proceso raíz mandará SIGTERM a sus hijos*/
    if(getpid() == root_pid){
        kill(son_pid, SIGTERM);
        if(signal(SIGTERM, SIG_IGN) == SIG_ERR){
            perror("signal");
            exit(EXIT_FAILURE);
        }
        pause();

    }
    else{
        if(padre != 1){
            son_pid = root_pid;
        }

        if(signal(SIGTERM, manejador_TERM) == SIG_ERR){
            perror("signal");
            exit(EXIT_FAILURE);
        }
        pause();
    }

    printf("Muere PID=%d\n", getpid());
    wait(&status);
    exit(EXIT_SUCCESS);

	return 0;
}

void manejador_USR1(int sig){
	printf("Proceso %d manda USR1  %d\n", getpid(), son_pid);
	//printf("Hola PID=%d, time= %s\n", son_pid, "por hacer");
	sleep(2);
	kill(son_pid, SIGUSR1);
}

void manejador_TERM(int sig) {
	sleep(1);
	kill(son_pid, SIGTERM);
	printf("Muere PID=%d\n", son_pid);
	wait(&status);
	exit(EXIT_SUCCESS);
}