/* Author: Daniel Walsh
 * Date: 4/28/21
 * Title: TCP Server
 * Purpose: Implement the server side of a TCP connection for one client
 */

 //Lab4: Concurrent server  

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/types.h>
#include <pthread.h>

#define NTHREADS 1 // 10 threads
#define CONN 1 // 10 connections

//void *threadF(void *arg); // thread function
//pthread_t threads[NTHREADS]; // thread ID array

struct d { 		//structure to hold thread data
   int con; //connection
   int fP; //file pointer
   int tID; //thread id
};

int main (int argc, char *argv[]){
    if (argc != 3){
		  printf ("Usage: %s <port number> <src_file> \n",argv[0]);
		  exit(1);
    }
    int		sockfd;             //Declare socket file descriptor
    char	buff[1024];           //Declare a buffer of size 1k bytes
    int fp, k, connfd;    // connection array
    
    //Declare server address to which to bind for receiving messages and client address to fill in sending address
    struct	sockaddr_in servAddr, clienAddr; 
    
    //Set server address/ port
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl (INADDR_ANY);
    servAddr.sin_port = htons (atoi (argv[1])); 
    
    //Open a TCP socket, if successful, returns a descriptor
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ){
      perror("Failure to setup an endpoint socket");
      exit(1);
    }
    
    //Set address/port of server endpoint for socket descriptor
    if (bind(sockfd, (struct sockaddr *)&servAddr, sizeof(struct sockaddr)) < 0){
      perror("Failure to bind server address to the endpoint socket");
      exit(1);
    } 

    // Server listening to the socket endpoint, and can queue 1 client requests
    listen(sockfd, 1); 

    k = 0; //connection index
    printf ("opening file %s\n", argv[2]);
    if ((fp = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC)) < 0){
      perror("Failure to open the file");
      exit(1);
    } 
    int sin_size = sizeof(struct sockaddr_in); //size of sockaddr_in
    
    //Server loops all the time accepting conncections when they are made, then passing connfd to a thread
    while (1) {
        //Server accepting to establish a connection with a connecting client, if successful, returns a connection descriptor
        if ((connfd = accept(sockfd, (struct sockaddr *)&clienAddr, (socklen_t *)&sin_size)) < 0){
          perror("Failure to accept connection to the client");
          exit(1);
        }
        //Connection established, server begins to read and write to the connecting client
        printf("Connection Established with client: IP %s and Port %d\n", inet_ntoa(clienAddr.sin_addr), ntohs(clienAddr.sin_port));
        //pthread_attr_t attr; 
      	//pthread_attr_init(&attr);
        struct d *data = (struct d *) malloc(sizeof(struct d)); //Data object to pass to thread
	      data->con = connfd;
	      data->fP= fp;
        data->tID = k;   
	      //pthread_create(/* your code to pass thread parameters */); //Thread to handle connfd
        	k++; 

	//receive and write connfd onto fp
	int filePass = recv(connfd, buff, sizeof(buff), 0);
	int bytes_written = write(fp, buff, filePass);
	printf("%d bytes written on %s\n", bytes_written, argv[2]);
	
	close(filePass);
	close(connfd);
	close(fp);
	
    }
    close(fp);
    close(sockfd);
    return 0;
}

//Thread function handling client connection
//void *threadF(void *arg){
  //your code to receive data from connection and write to file

//}

