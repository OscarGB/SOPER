#include  <stdio.h>
#include  <string.h>
#include  <sys/types.h>
#include  <sys/wait.h>
#include  <unistd.h>
#include  <stdlib.h>

#define   MAX_COUNT  50
#define   BUF_SIZE   100

void  main(void)
{
     pid_t  pid;
     int    i;
     char   buf[BUF_SIZE];
     pid_t hijo;
     int status = 0;

     hijo = fork();
     pid = getpid();
     if(hijo > 0){
     	waitpid(hijo, &status, 0);
     	sprintf(buf, "The status is %d\n", WTERMSIG(status));
        write(1, buf, strlen(buf));
     }
     for (i = 1; i <= MAX_COUNT; i++) {
          sprintf(buf, "This line is from pid %d, value = %d\n", pid, i);
          write(1, buf, strlen(buf));
          if(hijo == 0)
          	exit(2);
     } 
}