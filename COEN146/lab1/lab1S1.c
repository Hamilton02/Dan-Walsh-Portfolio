/*
 * Name: Daniel Walsh
 * Date: 4/7/21
 * Title: Lab 1 Step 1
 * Descritption: Creates 100 parent and child threads with fork
 */

#include <stdio.h>
      /* printf, stderr */
#include <sys/types.h>
  /* pid_t */
#include <unistd.h>
     /* fork */
#include <stdlib.h>
     /* atoi */
#include <errno.h>
      /* errno */

 /* main function with command-line arguments to pass */
int main(int argc, char *argv[]) {

    //creates the fork variable
    pid_t  pid;
    int i, n;

    //checks for executable
    if (argc !=2){
	fprintf(stderr,"usage: ./a.out <seconds> \n");
	exit(0);
    }

    n = atoi(argv[1]); // n microseconds to input from keyboard for delay  
    printf("\n Before forking.\n");

    //forks the process
    pid = fork();
    if (pid == -1) {
        fprintf(stderr, "can't fork, error %d\n", errno);
    }

    //forks into parent and child
    if (pid){
        // Parent process
        for (i=0;i<100;i++) {
            printf("\t \t \t Parent Process %d \n",i);
            usleep(n);
        }
    }else{
        // Child process
        for (i=0;i<100;i++) {
            printf("Child process %d\n",i);
            usleep(n);
        }
    }
    return 0;
}
