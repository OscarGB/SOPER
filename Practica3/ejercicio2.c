#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/ipc.h>
#include <string.h>
#include <errno.h>
#include <sys/shm.h>
#include <time.h>

#define FILEKEY "/bin/cat"
#define KEY 1300
#define MAXBUF 10

#define MAXTIME 20

typedef struct info {
    char nombre[80];
    int id;
}Info;


int main(int argc, char* argv[]){
    int n, i, key, id_zone;
    int bufferid;
    Info *buff;
    int pid = 3, padre_id;
    int sltime;
    char *buffer;
    
    void manejador_USR1();
    
    
    /* Control de argumentos de entrada */
    if(argc < 2){
        printf("Introduce un número de hijos a crear\n");
        return 1;
    }
    n = atoi(argv[1]);
    
    /*Creación de la clave*/
    key = ftok(FILEKEY, KEY);
    if(key < 0){
        printf("Error creando la key");
        return 1;
    }
    
    /*Conseguir id*/
    id_zone = shmget (key, sizeof(Info), IPC_CREAT | IPC_EXCL | SHM_R | SHM_W);
    if(id_zone < 0){
        printf("Error solicitando id para memoria compartida\n");
        return 1;
    }
    
    /*Attach de memoria*/
    buff = shmat(id_zone, (char *)0, 0);
    if(buff == NULL){
        printf("Error reservando memoria compartida\n");
        return 1;
    }
    
    /*Valor inicial del id*/
    buff->id = 0;
    
    padre_id = getpid();
    
    /*Bucle para la creación de procesos hijo*/
    for(i = 0; i < n; i ++) {
        if(pid != 0){
            pid = fork();
            
            if(pid < 0){
                perror("Error de fork");
                exit(EXIT_FAILURE);
            }
        }
        else{
           break; 
        }
    }
    if(pid != 0){
        i = 0;
        while(i < n){
            if(signal(SIGUSR1, manejador_USR1) == SIG_ERR){
                perror("signal");
                exit(EXIT_FAILURE);
            }
            pause();
            buffer = buff->nombre;
            bufferid = buff->id;
            fprintf(stdout, "id: %d, nombre: %s\n",bufferid, buffer);
            i++;
        }
    }

    else{
        
        id_zone = shmget (key, sizeof(Info), 0);
        if(id_zone < 0){
            printf("Error solicitando id para memoria compartida\n");
            return 1;
        }
        
        buff = shmat(id_zone, (char *)0, 0);
        if(buff == NULL){
            printf("Error reservando memoria compartida\n");
            return 1;
        }
        
         /*Obtenemos un tiempo aleatorio de espera*/
        srand(getpid());
        sltime = (int)(((float)rand() / (float)RAND_MAX) * (float)MAXTIME);
        sleep(sltime);
        
        fprintf(stdout, "Introduce el nombre del cliente: ");
        fscanf(stdin, "%s", buff->nombre);
        (buff->id)++;
        
        kill(padre_id, SIGUSR1);
        
        
        shmdt((char *)buff);
        
        exit(EXIT_SUCCESS);
    }
    
    

    while(wait(NULL) > 0);
    
    shmdt((char *)buff);
    shmctl(id_zone, IPC_RMID, (struct shmid_ds *)NULL);
    
    exit(EXIT_SUCCESS);
    
}

void manejador_USR1(int signal){
    return;
}