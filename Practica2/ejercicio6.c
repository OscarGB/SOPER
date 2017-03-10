/**
* @file ejercicio6.c
* @author Jose Ignacio Garcia, Óscar Gómez
* @date 10-03-2017
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(){
	int pid, status;

	pid = fork();

	while(pid == 0){
		printf("Soy el proceso hijo con PID: %d\n", getpid());
		sleep(5);
	}

	sleep(30);
	status = kill(pid, SIGKILL);
	return 0;
}