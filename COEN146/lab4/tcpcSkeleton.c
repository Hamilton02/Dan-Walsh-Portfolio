/* Author: Daniel Walsh
 * Date: 4/28/21
 * Title: TCP Client
 * Purpose: Implement a TCP client connection
 */

//Lab4: Client

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <errno.h>
#include <arpa/inet.h> 


int main (int argc, char *argv[]) {
    int		sockfd = 0, n = 0;
    char	buff[1024];
    struct	sockaddr_in servAddr; 
    int		fp;

    if (argc != 4){
	    printf ("Usage: %s <port no>  <ip of server> <src_file> \n",argv[0]);
	    exit (1);
    } 
    //Create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("Failure to setup an endpoint socket");
        exit(1);
    } 

    //Set server address by filling sevAddr fields
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(atoi (argv[1])); 
    struct hostent *host = ((struct hostent * )gethostbyname(argv[2]));
    servAddr.sin_addr = *((struct in_addr *)host->h_addr);

    //Connet to server
    if (connect(sockfd, (struct sockaddr *)&servAddr, sizeof(struct sockaddr)) < 0){
		perror("Failure to connect to the server");
        exit(1);
    } 
    //Open file
    if ((fp = open(argv[3], O_RDONLY)) < 1) {
		printf("fp: %d, name: %s\n", fp, argv[3]);
		perror("Failure to open the file");
        exit(1);
    }
    
    //read the passed file and sent it to the server
    int count=1, bytes_written;
    int bytes_read = read(fp, buff, sizeof(buff));
    if((bytes_written = send(sockfd, buff, bytes_read, 0)) < 0){
                perror("Failure to send file");
        exit(1);
    }
  
    printf("%d bytes written: to the server from %\n", bytes_written, argv[2]);
 
    close (fp);
    close (sockfd);
    return 0;
}
