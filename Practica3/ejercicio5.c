#include "test.h"
#include "semaforos.h"
#define MAX_TESTS 8
#define SEMKEY 75768
#define NSEMAFOROS 2

/*Crear un semáforo*/
BOOL test_semaforos1(){
    int semid;
    int status;
    
    status = Crear_Semaforo(SEMKEY, NSEMAFOROS, &semid);
    if(status == ERROR){
        TEST_PRINT(FALSE);
        return FALSE;
    }
    else if(status == 1){
        fprintf(stderr, "Libere semáforos y vuelva a correr la prueba. \n");
        TEST_PRINT(FALSE);
        return FALSE;
    }
    
    /*Liberamos los semáforos empleados*/
    semctl(semid, 0, IPC_RMID, 0);
    
    TEST_PRINT(TRUE);
    return TRUE;
}

/*Inicializar un semáforo*/
BOOL test_semaforos2(){
    int semid, i;
    int status;
    unsigned short array[NSEMAFOROS];

    for (i = 0; i < NSEMAFOROS; i++){
    	array[i] = 1;
    }

    
    /*Asumimos que la función de cración funciona correctamente*/
    status = Crear_Semaforo(SEMKEY, NSEMAFOROS, &semid);

    if(status == 1){
        fprintf(stderr, "Libere semáforos y vuelva a correr la prueba. \n");
        TEST_PRINT(FALSE);
        return FALSE;
    }

    /*Inicializamos comprobando errores*/
    if(Inicializar_Semaforo(semid, array) == ERROR){
    	TEST_PRINT(FALSE);

    	/*Liberamos los semáforos empleados*/
   	 	semctl(semid, 0, IPC_RMID, 0);

   	 	return FALSE;
    }
    
    /*Liberamos los semáforos empleados*/
    semctl(semid, 0, IPC_RMID, 0);
    
    TEST_PRINT(TRUE);
    return TRUE;
}

/*Borrar un semáforo*/
BOOL test_semaforos3(){
    int semid, i;
    int status;

    
    /*Asumimos que la función de cración funciona correctamente*/
    status = Crear_Semaforo(SEMKEY, NSEMAFOROS, &semid);

    if(status == 1){
        fprintf(stderr, "Libere semáforos y vuelva a correr la prueba. \n");
        TEST_PRINT(FALSE);
        return FALSE;
    }

    /*Borramos comprobando errores*/
    if(Borrar_Semaforo(semid) == ERROR){
    	TEST_PRINT(FALSE);

    	/*Liberamos los semáforos empleados*/
   	 	semctl(semid, 0, IPC_RMID, 0);

   	 	return FALSE;
    }

    /*Liberamos los semáforos empleados*/
    //semctl(semid, 0, IPC_RMID, 0);
    
    TEST_PRINT(TRUE);
    return TRUE;
}

/*Borrar un semáforo vacío*/
BOOL test_semaforos4(){
    int semid, i;
    int status;

    /*Borramos comprobando errores*/
    if(Borrar_Semaforo(semid) != ERROR){
    	TEST_PRINT(FALSE);

    	/*Liberamos los semáforos empleados*/
   	 	semctl(semid, 0, IPC_RMID, 0);

   	 	return FALSE;
    }


    
    TEST_PRINT(TRUE);
    return TRUE;
}

/*Down de un semáforo*/
BOOL test_semaforos5(){
    int semid, i;
    int status;
    unsigned short array[NSEMAFOROS];

    for (i = 0; i < NSEMAFOROS; i++){
    	array[i] = 2; /*Lo seteamos a 2 para que al hacer un down
    	no se bloquee el proceso*/
    }

    /*Asumimos que la función de cración funciona correctamente*/
    status = Crear_Semaforo(SEMKEY, NSEMAFOROS, &semid);

    if(status == 1){
        fprintf(stderr, "Libere semáforos y vuelva a correr la prueba. \n");
        TEST_PRINT(FALSE);
        return FALSE;
    }

    /*Como ya hemos probado la función, asumimos correcto funcionamiento, 
    ya que nos interesa centrarnos en los errores del Down*/
    Inicializar_Semaforo(semid, array);

    if(Down_Semaforo(semid, 0, SEM_UNDO) == ERROR){
    	TEST_PRINT(FALSE);

    	/*Liberamos los semáforos empleados*/
   		semctl(semid, 0, IPC_RMID, 0);

    	return(FALSE);
    }

    /*Liberamos los semáforos empleados*/
    semctl(semid, 0, IPC_RMID, 0);
    
    TEST_PRINT(TRUE);
    return TRUE;
}


/*Down de un semáforo que no está en el array de semáforos*/
BOOL test_semaforos6(){
    int semid, i;
    int status;
    unsigned short array[NSEMAFOROS];

    for (i = 0; i < NSEMAFOROS; i++){
    	array[i] = 2;
    }

    /*Asumimos que la función de cración funciona correctamente*/
    status = Crear_Semaforo(SEMKEY, NSEMAFOROS, &semid);

    if(status == 1){
        fprintf(stderr, "Libere semáforos y vuelva a correr la prueba. \n");
        TEST_PRINT(FALSE);
        return FALSE;
    }

    /*Como ya hemos probado la función, asumimos correcto funcionamiento, 
    ya que nos interesa centrarnos en los errores del Down*/
    Inicializar_Semaforo(semid, array);

    /*Debería devolver error, ya que el semáforo no está en el array*/
    if(Down_Semaforo(semid, 3, SEM_UNDO) != ERROR){
    	TEST_PRINT(FALSE);

    	/*Liberamos los semáforos empleados*/
   		semctl(semid, 0, IPC_RMID, 0);

    	return(FALSE);
    }

    /*Liberamos los semáforos empleados*/
    semctl(semid, 0, IPC_RMID, 0);
    
    TEST_PRINT(TRUE);
    return TRUE;
}

/*Down de un semáforo no creado*/
BOOL test_semaforos7(){
    int semid, i;
    int status;

    /*Debería devolver error, ya que el semáforo no está creado*/
    if(Down_Semaforo(semid, 3, SEM_UNDO) != ERROR){
    	TEST_PRINT(FALSE);
    	return(FALSE);
    }
    
    TEST_PRINT(TRUE);
    return TRUE;
}

/*Down múltiple de un semáforo*/
BOOL test_semaforos8(){
    int semid, i;
    int status;
    unsigned short array[NSEMAFOROS];
    int active[NSEMAFOROS];

    for (i = 0; i < NSEMAFOROS; i++){
    	array[i] = 2; /*Lo seteamos a 2 para que al hacer un down
    	no se bloquee el proceso*/
    }

    for (i = 0; i < NSEMAFOROS; i++){
    	active[i] = i; /*Array de posiciones de semáforos*/
    }

    /*Asumimos que la función de cración funciona correctamente*/
    status = Crear_Semaforo(SEMKEY, NSEMAFOROS, &semid);

    if(status == 1){
        fprintf(stderr, "Libere semáforos y vuelva a correr la prueba. \n");
        TEST_PRINT(FALSE);
        return FALSE;
    }

    /*Como ya hemos probado la función, asumimos correcto funcionamiento, 
    ya que nos interesa centrarnos en los errores del Down*/
    Inicializar_Semaforo(semid, array);

    if(DownMultiple_Semaforo(semid, NSEMAFOROS, SEM_UNDO, active) == ERROR){
    	TEST_PRINT(FALSE);

    	/*Liberamos los semáforos empleados*/
   		semctl(semid, 0, IPC_RMID, 0);

    	return(FALSE);
    }

    /*Liberamos los semáforos empleados*/
    semctl(semid, 0, IPC_RMID, 0);
    
    TEST_PRINT(TRUE);
    return TRUE;
}

/*Up de un semáforo*/
BOOL test_semaforos9(){
    int semid, i;
    int status;
    unsigned short array[NSEMAFOROS];

    for (i = 0; i < NSEMAFOROS; i++){
    	array[i] = 2; /*Lo seteamos a 2 para que al hacer un Up
    	no se bloquee el proceso*/
    }

    /*Asumimos que la función de cración funciona correctamente*/
    status = Crear_Semaforo(SEMKEY, NSEMAFOROS, &semid);

    if(status == 1){
        fprintf(stderr, "Libere semáforos y vuelva a correr la prueba. \n");
        TEST_PRINT(FALSE);
        return FALSE;
    }

    /*Como ya hemos probado la función, asumimos correcto funcionamiento, 
    ya que nos interesa centrarnos en los errores del Up*/
    Inicializar_Semaforo(semid, array);

    if(Up_Semaforo(semid, 0, SEM_UNDO) == ERROR){
    	TEST_PRINT(FALSE);

    	/*Liberamos los semáforos empleados*/
   		semctl(semid, 0, IPC_RMID, 0);

    	return(FALSE);
    }

    /*Liberamos los semáforos empleados*/
    semctl(semid, 0, IPC_RMID, 0);
    
    TEST_PRINT(TRUE);
    return TRUE;
}


/*Up de un semáforo que no está en el array de semáforos*/
BOOL test_semaforos10(){
    int semid, i;
    int status;
    unsigned short array[NSEMAFOROS];

    for (i = 0; i < NSEMAFOROS; i++){
    	array[i] = 2;
    }

    /*Asumimos que la función de cración funciona correctamente*/
    status = Crear_Semaforo(SEMKEY, NSEMAFOROS, &semid);

    if(status == 1){
        fprintf(stderr, "Libere semáforos y vuelva a correr la prueba. \n");
        TEST_PRINT(FALSE);
        return FALSE;
    }

    /*Como ya hemos probado la función, asumimos correcto funcionamiento, 
    ya que nos interesa centrarnos en los errores del Up*/
    Inicializar_Semaforo(semid, array);

    /*Debería devolver error, ya que el semáforo no está en el array*/
    if(Up_Semaforo(semid, 3, SEM_UNDO) != ERROR){
    	TEST_PRINT(FALSE);

    	/*Liberamos los semáforos empleados*/
   		semctl(semid, 0, IPC_RMID, 0);

    	return(FALSE);
    }

    /*Liberamos los semáforos empleados*/
    semctl(semid, 0, IPC_RMID, 0);
    
    TEST_PRINT(TRUE);
    return TRUE;
}

/*Up de un semáforo no creado*/
BOOL test_semaforos11(){
    int semid, i;
    int status;

    /*Debería devolver error, ya que el semáforo no está creado*/
    if(Up_Semaforo(semid, 3, SEM_UNDO) != ERROR){
    	TEST_PRINT(FALSE);
    	return(FALSE);
    }
    
    TEST_PRINT(TRUE);
    return TRUE;
}

/*Up múltiple de un semáforo*/
BOOL test_semaforos12(){
    int semid, i;
    int status;
    unsigned short array[NSEMAFOROS];
    int active[NSEMAFOROS];

    for (i = 0; i < NSEMAFOROS; i++){
    	array[i] = 2; /*Lo seteamos a 2 para que al hacer un Up
    	no se bloquee el proceso*/
    }

    for (i = 0; i < NSEMAFOROS; i++){
    	active[i] = i; /*Array de posiciones de semáforos*/
    }

    /*Asumimos que la función de cración funciona correctamente*/
    status = Crear_Semaforo(SEMKEY, NSEMAFOROS, &semid);

    if(status == 1){
        fprintf(stderr, "Libere semáforos y vuelva a correr la prueba. \n");
        TEST_PRINT(FALSE);
        return FALSE;
    }

    /*Como ya hemos probado la función, asumimos correcto funcionamiento, 
    ya que nos interesa centrarnos en los errores del Up*/
    Inicializar_Semaforo(semid, array);

    if(UpMultiple_Semaforo(semid, NSEMAFOROS, SEM_UNDO, active) == ERROR){
    	TEST_PRINT(FALSE);

    	/*Liberamos los semáforos empleados*/
   		semctl(semid, 0, IPC_RMID, 0);

    	return(FALSE);
    }

    /*Liberamos los semáforos empleados*/
    semctl(semid, 0, IPC_RMID, 0);
    
    TEST_PRINT(TRUE);
    return TRUE;
}





int main(int argc, char* argv[]){
	int test = 0;
	int todas = 1;

	if(argc < 2){
		printf("Pasando todas las pruebas a la biblioteca semáforos:\n");
	}else{
		test = atoi(argv[1]);
		todas = 0;
		if(test < 1 || test > MAX_TESTS){
			printf("Error, prueba no reconocida\n");
			exit(EXIT_SUCCESS);
		}
		printf("Pasando la prueba numero %d al modulo semáforos: \n", test);
	}

	if(todas || test == 1) test_semaforos1();
	if(todas || test == 2) test_semaforos2();
	if(todas || test == 3) test_semaforos3();
	if(todas || test == 4) test_semaforos4();
	if(todas || test == 5) test_semaforos5();
	if(todas || test == 6) test_semaforos6();
	if(todas || test == 7) test_semaforos7();
	if(todas || test == 8) test_semaforos8();
	if(todas || test == 9) test_semaforos9();
	if(todas || test == 10) test_semaforos10();
	if(todas || test == 11) test_semaforos11();
	if(todas || test == 12) test_semaforos12();


	PRINT_RESULTS();

	return 0;
}