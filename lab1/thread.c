
/*
 * Name: Daniel Walsh
 * Date: 4/7/21
 * Title: Step 5: pthread create
 * Description: Create two threads with pthread_create
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
#include <pthread.h>

//declares print function
void *print_message_function( void *ptr);

 /* main function with command-line arguments to pass */
int main(int argc, char *argv[]) {

    //creates two pthreads
    pthread_t  thread1, thread2;

    //creates two ints for the create thread
    int iret1, iret2, n;

    //messages to pass the message function
    char* message1 = "Thread 1";
    char* message2 = "Thread 2";

    //checks if no executable
    if (argc !=2){
	fprintf(stderr,"usage: ./a.out <seconds> \n");
	exit(0);
    }

    n = atoi(argv[1]); // n microseconds to input from keyboard for delay  


    printf("\n Before Threading\n");

    //creates two threads
    iret1 = pthread_create(&thread1, NULL, print_message_function, message1);
    iret2 = pthread_create(&thread2, NULL, print_message_function, message2);

    //waits for the threads to finish
    pthread_join( thread1, NULL);
    pthread_join( thread2, NULL);

    //prints the thread returns
    printf("Thread 1 Returns: %d\n", iret1);
    printf("Thread 2 Returns: %d\n", iret2);
    exit(0);
    return 0;
}

void *print_message_function( void *ptr){

    //takes void and makes it into a char to print out
    char *message;
    message = (char *) ptr;
    printf("%s \n", message);
}
