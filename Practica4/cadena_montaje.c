#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define N_PROCESOS 3
#define N 18976
#define TAM 4056
#define IN 0
#define OUT 1

typedef struct _Mensaje {
    long mtype; /*Identificador del mensaje*/
    
    /*Informacion del mensaje*/
    char buffer[TAM];
    
} mensaje;

int main(int argc, char *argv[]){
    int pid, msqid;
    char proceso;
    key_t clave;
    mensaje msg; 
    char *ficheros[2];
    FILE *f = NULL;
    int len, i;
    struct msqid_ds ds;
    
    /*Comprobación de argumentos*/
    if(argc < 2){
        perror("Introduzca dos ficheros de entrada\n");
        exit(EXIT_FAILURE);
    }
    
    ficheros[IN] = argv[1];
    ficheros[OUT] = argv[2];
    
    if(strcmp(ficheros[IN], ficheros[OUT]) == 0){
        perror("Introduzca dos ficheros diferentes\n");
        exit(EXIT_FAILURE);
    }
    
    /*Creamos la clave*/
    clave = ftok ("/bin/ls", N); 
    if (clave == (key_t) -1){
        perror("Error al obtener clave para cola mensajes\n");
        exit(EXIT_FAILURE); 
    } 
    
    /*Solicitamos la cola de mensajes*/
    msqid = msgget (clave, 0600 | IPC_CREAT);
    if (msqid == -1){
        perror("Error al obtener identificador para cola mensajes\n");
        exit(EXIT_FAILURE); 
    } 
    
    msgctl(msqid, MSG_STAT, &ds);
    
    proceso = 'A';
    pid = fork();
    
    if(pid < 0){
        perror("Error de fork");
        exit(EXIT_FAILURE);
    }
    
    else if(pid == 0){
        pid = fork();
        if(pid < 0){
            perror("Error de fork");
            exit(EXIT_FAILURE);
        }
        
        if(pid == 0){
            proceso = 'C'; /*Tercer proceso*/
        }
        else{
            proceso = 'B'; /*Segundo proceso*/
        }
    }
    
    /*Parte del primer proceso, lee el fichero de entrada*/
    if(proceso == 'A'){
        /*Abrimos el fichero de entrada*/
        f = fopen(ficheros[IN], "r");
        if(!f){
            perror("Error de lectura de fichero.");
            msgctl (msqid, IPC_RMID, (struct msqid_ds *)NULL); 
            exit(EXIT_FAILURE);
        }
        
        while(fgets(msg.buffer, TAM, f) != NULL){
        
            msg.mtype = 1;
            /*Enviamos el mensaje*/
            msgsnd(msqid, (struct msgbuf*) &msg, sizeof(mensaje) - sizeof(long), 0);
           
        }
        
        /*El mensaje con EOF indica fin de ecritura*/
        msg.buffer[0] = EOF;
        msg.buffer[1] = '\0';
        
        msgsnd(msqid, (struct msgbuf*) &msg, sizeof(mensaje) - sizeof(long), 0);
        
        fclose(f);
        
        while(wait(NULL) > 0);
        
       msgctl(msqid, IPC_RMID, NULL);
        
        exit(EXIT_SUCCESS);
        
        
    }
    
    /*Parte del segundo proceso, cambia de mayusculas a minúsculas*/
    if(proceso == 'B'){
        while(1){
            msgrcv (msqid, (struct msgbuf *) &msg, sizeof(mensaje) - sizeof(long), 1, 0);
            len = strlen(msg.buffer);
            if(len == 1){
                if(msg.buffer[0] == EOF){
                    /*Mandamos un mensaje con EOF para notificar al proceso 3 de que hemos acabado*/
                    msg.mtype = 2;
                    msg.buffer[0] = EOF;
                    msg.buffer[1] = '\0';
            
                    msgsnd(msqid, (struct msgbuf*) &msg, sizeof(mensaje) - sizeof(long), 0);
                    
                    while(wait(NULL) > 0);
                    
                    exit(EXIT_SUCCESS);
                }
            }
            /*Cambiamos de minusculas a mayusculas*/
            for(i=0; i < len; i++){
                if(msg.buffer[i] >= 'a'){
                    msg.buffer[i] = msg.buffer[i] - 32;
                }
            }
            msg.mtype = 2;
            
            /*Enviamos el mensaje*/
            msgsnd(msqid, (struct msgbuf*) &msg, sizeof(mensaje) - sizeof(long), 0);
        }
        
    }
    
    if(proceso == 'C'){
        f = fopen(ficheros[OUT], "w");
        if(!f){
            perror("Error de apertura de fichero.");
            exit(EXIT_FAILURE);
        }
        
        while(1){
            msgrcv (msqid, (struct msgbuf *) &msg, sizeof(mensaje) - sizeof(long), 2, 0);
            len = strlen(msg.buffer);
            if(len == 1){
                if(msg.buffer[0] == EOF){
                    fclose(f);
                    exit(EXIT_SUCCESS);
                }
            }
            
            fprintf(f,"%s", msg.buffer);
  
        }
        
    }
    
    exit(EXIT_SUCCESS);
}