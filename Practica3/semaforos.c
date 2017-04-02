#include "semaforos.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <errno.h>
#include <stdlib.h>

/*
 * Declaración de la union
 */
union semun {
    int val;
    struct semid_ds *semstat;
    unsigned short *array;
};

/***************************************************************
Nombre:
    Inicializar_Semaforo.
Descripcion:
    Inicializa los semaforos indicados.
Entrada:
    int semid: Identificador del semaforo.
    unsigned short *array: Valores iniciales.
Salida:
    int: OK si todo fue correcto, ERROR en caso de error.
************************************************************/
int Inicializar_Semaforo(int semid, unsigned short *array) {
    union semun arg;
    
    if(!array){
        fprintf(stderr, "array sin declarar\n");
        return ERROR;
    }
    
    arg.array = array;
    
    if(semctl(semid, 0, SETALL, arg) == -1) {
        fprintf(stderr, "Error %d", errno);
        
        if(errno == EINVAL){
            fprintf(stderr, ": semáforo no creado");
        }
        
        fprintf(stdout, "\n");
        exit(errno);
    }
    
    return OK;
    
}
   

/***************************************************************
Nombre: Borrar_Semaforo.
    Descripcion: Borra un semaforo.
Entrada:
    int semid: Identificador del semaforo.
Salida:
    int: OK si todo fue correcto, ERROR en caso de error.
***************************************************************/
int Borrar_Semaforo(int semid) {
    
    if(semctl(semid, 0, IPC_RMID, 0) == -1){
        fprintf(stdout, "Error al borrar semáforos. \n");
        return ERROR;
    }
    return OK;
}

/***************************************************************
Nombre: 
    Crear_Semaforo.
Descripcion: 
    Crea un semaforo con la clave y el tamaño especificado. Lo inicializa a 0.
Entrada:
    key_t key: Clave precompartida del semaforo.
    int size: Tamaño del semaforo.
Salida:
    int *semid: Identificador del semaforo.
    int: ERROR en caso de error,
    0 si ha creado el semaforo,
    1 si ya estaba creado.
**************************************************************/
int Crear_Semaforo(key_t key, int size, int *semid){
    
    if(key <= 0 || size <= 0){
        return ERROR;
    }
    
    *semid = semget(key, size, IPC_CREAT | IPC_EXCL | SHM_R | SHM_W);
    
    if((*semid == -1) && errno == EEXIST){
        return 1;
    }
        
    if(*semid==-1){
        fprintf(stderr, "Error en la reserva del semaforo\n");
        return ERROR;
    }
    
    return 0;
}

/**************************************************************
Nombre:
    Down_Semaforo
Descripcion: 
    Baja el semaforo indicado
Entrada:
    int semid: Identificador del semaforo.
    int num_sem: Semaforo dentro del array.
    int undo: Flag de modo persistente pese a finalización abrupta.
Salida:
    int: OK si todo fue correcto, ERROR en caso de error.
***************************************************************/
int Down_Semaforo(int id, int num_sem, int undo){
    struct sembuf sem_oper;
    
    /*Control de errores*/
    if(id <= 0 || num_sem < 0 || undo < 0){
        return ERROR;
    }
    
    /*Damos valores a la estructura*/
    sem_oper.sem_num = num_sem;
    sem_oper.sem_op = -1;
    sem_oper.sem_flg = undo;
    
    /*Llamamos a semop y comprobamos errores*/
    if(semop(id, &(sem_oper), 1) == -1){
        fprintf(stderr, "Error al hacer down del semáforo\n");
        return ERROR;
    }
    return OK;  
    
}
/***************************************************************
Nombre: 
    DownMultiple_Semaforo
Descripcion: 
    Baja todos los semaforos del array indicado por active.
Entrada:
    int semid: Identificador del semaforo.
    int size: Numero de semaforos del array.
    int undo: Flag de modo persistente pese a finalización abrupta.
    int *active: Semaforos involucrados.
Salida:
    int: OK si todo fue correcto, ERROR en caso de error.
***************************************************************/
int DownMultiple_Semaforo(int id,int size,int undo,int *active) {
    struct sembuf sem_oper;
    int i;
    
    /*Control de errores*/
    if(id <= 0 || size <= 0 || size <= 0 || !active) {
        return ERROR;
    }
    
    /*Bucle para hacer un down a todos los semáforos*/
    for(i == 0; i < size; i++){
        /*Llamamos a la función de Down*/
        if(Down_Semaforo(id, active[i], undo) == ERROR){
            return ERROR;
        }
        
    }
    
    return OK;
    
}

/**************************************************************
Nombre:
    Up_Semaforo
Descripcion: 
    Sube el semaforo indicado
Entrada:
    int semid: Identificador del semaforo.
    int num_sem: Semaforo dentro del array.
    int undo: Flag de modo persistente pese a finalizacion abupta.
Salida:
    int: OK si todo fue correcto, ERROR en caso de error.
***************************************************************/
int Up_Semaforo(int id, int num_sem, int undo) {
    struct sembuf sem_oper;
    
    /*Control de errores*/
    if(id <= 0 || num_sem < 0 || undo < 0){
        return ERROR;
    }
    
    /*Damos valores a la estructura*/
    sem_oper.sem_num = num_sem;
    sem_oper.sem_op = 1;
    sem_oper.sem_flg = undo;
    
    /*Llamamos a semop y comprobamos errores*/
    if(semop(id, &(sem_oper), 1) == ERROR){
        fprintf(stderr, "Error al hacer up del semáforo\n");
        return ERROR;
    }
    return OK;
}

/***************************************************************
Nombre: 
    UpMultiple_Semaforo
Descripcion: 
    Sube todos los semaforos del array indicado por active.
Entrada:
    int semid: Identificador del semaforo.
    int size: Numero de semaforos del array.
    int undo: Flag de modo persistente pese a finalización abrupta.
    int *active: Semaforos involucrados.
Salida:
    int: OK si todo fue correcto, ERROR en caso de error.
***************************************************************/
int UpMultiple_Semaforo(int id,int size, int undo, int *active) {
    struct sembuf sem_oper;
    int i;
    
    /*Control de errores*/
    if(id <= 0 || size <= 0 || size <= 0 || !active) {
        return ERROR;
    }
    
    /*Bucle para hacer un up a todos los semáforos*/
    for(i == 0; i < size; i++){
        /*Llamamos a la función de Up*/
        if(Up_Semaforo(id, active[i], undo) == ERROR){
            return ERROR;
        }
        
    }
    
    return OK;
}