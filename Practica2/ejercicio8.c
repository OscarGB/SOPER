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
#include <time.h>

#define NUM_PROC 4 /*!< Ńumero de iteraciones*/

int son_pid; /*!< Variable para almacenar el pid del proceso hijo*/
int root_pid; /*!<Variable para almacenar el pid del proceso root*/
int status; /*!< Variable de estado para los wait*/

time_t tiempo; /*!< Variables necesarias para trabajar con tiempos*/
struct tm *tlocal;
char output[128]; /*!< Variable donde almacenaremos la fecha y hora*/


int main(int argc, char const *argv[]) {
    int numproc, vueltas, v = 0;
    int i;
    int pid = 0; /*!< Fijamos pid a 0 para que efectúe un fork()
                    en la primera iteración del bucle*/

    void manejador_USR1();
    void manejador_TERM();
    void manejador_FIN();

    

    if(argc < 3 || argc > 3) {
        printf("Prueba con: ./ejercicio8 <numero_procesos> <numero_vueltas>\n");
        return 1;
    }

    numproc = atoi(argv[1]);
    vueltas = atoi(argv[2]);

    root_pid = getpid(); /*Guardamos el pid del proceso raíz*/

    for(i = 0; i < numproc; i++){
        if(pid == 0){/*Para generar árboles en serie
                    sólo harán forks los hijos*/
            if((pid = fork()) < 0) { 
                perror("Error de fork");
                exit(EXIT_FAILURE);
            }

            else if(i == numproc - 1 && pid == 0){ /*Si es el último proceso,
                                            gestiona la primera señal*/
                son_pid = root_pid; /*El último proceso mandará señales al root*/
                sleep(5);
                kill(son_pid, SIGUSR1);
                break;
            }
            else if (pid > 0) {
                son_pid = pid;
                break;
            }
        }
        else{
            son_pid = pid; /*El pid obtenido en el fork será el pid del hijo*/
            break;
        }
    }

    /*Ahora vamos a gestionar el envío circular de señales*/

    while(v <= vueltas){

        /*Armamos la llegada de señales*/
        if(signal(SIGUSR1, manejador_USR1) == SIG_ERR){
            perror("signal");
            exit(EXIT_FAILURE);
        }
        if(signal(SIGTERM, manejador_TERM) == SIG_ERR){
            perror("signal");
            exit(EXIT_FAILURE);
        }
        

        pause(); /*Los procesos esperan la llegada de una señal*/

        v++;

    }

    /*Ahora el root iniciará una cadena de llamadas a TERM*/
    if(getpid() != root_pid) {

        pause(); /*Espera la llegada de una señal SIGTERM*/

    }
    else {
        kill(son_pid, SIGTERM);
        if(signal(SIGTERM, manejador_FIN) == SIG_ERR){
            perror("signal");
            exit(EXIT_FAILURE);
        }

        pause(); /*Espera la llegada de una señal SIGTERM, pero la 
                ignorará para ejecutar el código siguiente*/
    }

    /*A continuación, el root debería ser el único capaz de llegar hasta
    aquí, por lo que realizará un wait y morirá*/
    printf("Muere PID=%d\n", getpid());
    wait(&status);
    exit(EXIT_SUCCESS);

    return 0;
}

/**
* Manejador para la señal USR1
* @author Jose Ignacio Gomez, Óscar Gómez
* @date 16-03-2017
* @param int signal
*/
void manejador_USR1(int signal){
    tiempo = time(0);
    tlocal = localtime(&tiempo);
    strftime(output, 128, "%d/%m/%y %H:%M:%S", tlocal);
    printf("Hola PID=%d, time= %s\n", getpid(), output);
    sleep(2);
    kill(son_pid, SIGUSR1);
}

/**
* Manejador para la señal TERM
* @author Jose Ignacio Gomez, Óscar Gómez
* @date 16-03-2017
* @param int signal
*/
void manejador_TERM(int signal){
    sleep(1);
    kill(son_pid, SIGTERM);
    printf("Muere PID=%d\n", getpid());
    wait(&status);
    exit(EXIT_SUCCESS);
}

/**
* Manejador para la señal TERM del proceso root
* @author Jose Ignacio Gomez, Óscar Gómez
* @date 16-03-2017
* @param int signal
*/
void manejador_FIN(int signal) {
    printf("Muere PID=%d\n", getpid());
    wait(&status);
    exit(EXIT_SUCCESS);
}