#include <stdio.h>
#include <signal.h>

int main(){
	int pid, status;

	pid = fork();

	while(pid == 0){
		printf("Soy el proceso hijo con PID: %d", getpid());
		sleep(5);
	}

	sleep(30);
	status = kill(pid, SIGKILL);
	return 0
}