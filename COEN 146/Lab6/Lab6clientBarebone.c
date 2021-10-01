/*
 * Author: Daniel Walsh
 * Date: 5/19/21
 * Title: rdt 3.0 Client
 * Purpose: Implement rdt 3.0 for the client side
 */

//Lab6 Client
#include "lab6.h"

//getChecksum()
int getChecksum(Packet packet) {
    packet.header.cksum = 0;
    int checksum = 0;
    char *ptr = (char *)&packet;
    char *end = ptr + sizeof(Header) + packet.header.len;
    while (ptr < end) {
        checksum ^= *ptr++;
    } 
        return checksum;
}

void printPacket(Packet packet) {
    printf("Packet{ header: { seq_ack: %d, len: %d, cksum: %d }, data: \"",
            packet.header.seq_ack,
            packet.header.len,
            packet.header.cksum);
    fwrite(packet.data, (size_t)packet.header.len, 1, stdout);
    printf("\" }\n");
}

void ClientSend(int sockfd, const struct sockaddr *address, socklen_t addrlen, Packet packet, unsigned retries) {
    while (1) {
        //if retries is greater than 3, we give up and move on
	    if(retries>=3){
		    break;
	    }
        // calculate the checksum
        packet.header.cksum = getChecksum(packet);
        
        // Print what is being sent
        printf("Created: ");
        printPacket(packet);

        // Simulate lost packet.
        if (rand() % PLOSTMSG != 0) {
            printf("Dropping packet\n");
        } else {
           int bytes_sent = sendto(sockfd, (void*)&packet, sizeof(packet), 0, (struct sockaddr *)address, addrlen);
           printf("Packet sent: \n");
        }

        // wait until an ACK is received or timeout using select statement
        // recall recvfrom() is a blocking function, i.e. blocks until data is available
        // so what if data from server got lost, so select() solves this problem. type man select for more information.

        struct timeval tv;
        tv.tv_sec = 1;
        tv.tv_usec = 0;
        int rv;
        //setup select parameters
        fd_set readfds;
        fcntl(sockfd,F_SETFL,O_NONBLOCK);
        //start before calling select
        FD_ZERO(&readfds);
        FD_SET(sockfd,&readfds);
        //call select. sockfd+1 is used because select checks upto sockfd-1 descriptors.
        rv=select(sockfd+1,&readfds,NULL,NULL,&tv);
        if(rv==0){ // no data has been received
            printf("Timeout\n");
            //increment retries if packet is dropped
            retries++;
        }
        else{ //if rv!=0, there is something to receive
            // receive an ACK from the server
            Packet recvpacket;
            recvfrom(sockfd, (void*)&recvpacket, sizeof(recvpacket), 0, (struct sockaddr*)address, &addrlen);
            int e_cksum = getChecksum(recvpacket);

            // print what was received
            printf("Received ACK %d, checksum %d - ", recvpacket.header.seq_ack, recvpacket.header.cksum);

            // validate the ACK
            if (recvpacket.header.cksum != e_cksum) {
                // bad checksum, resend packet
                printf("Bad checksum, expected %d\n", e_cksum);
            } else if (recvpacket.header.seq_ack!=packet.header.seq_ack) {
                // incorrect sequence number, resend packet
                printf("Bad seqnum, expected %d\n", packet.header.seq_ack);
            } else {
                // good ACK, we're done
                printf("Good ACK\n");
                break;
            }
        }
    }
    printf("\n");
}

int main(int argc, char *argv[]){
    // check arguments

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <ip> <port> <infile>\n", argv[0]);
        return 1;
    }

    // seed the RNG
    srand((unsigned)time(NULL));

    // create and configure the socket
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
		perror("Failure to setup an endpoint socket");
        exit(1);
    }

    // initialize the server address structure
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    socklen_t addr_len = sizeof(address);
    struct hostent *host;
    host = (struct hostent *) gethostbyname(argv[1]);
    address.sin_port = htons(atoi(argv[2]));
    address.sin_family = AF_INET;
    address.sin_addr = *((struct in_addr *)host->h_addr);


    // open file
    int fp = open(argv[3], O_RDWR);
    if (fp < 0) {
        perror("Failed to open file\n");
        exit(1);
    }

    // send file contents to server
    Packet packet;
    int seq = 0;
    int retries = 0; 

    while(read(fp,packet.data, sizeof(packet.data)) > 0){
        packet.header.seq_ack = seq;
        packet.header.len = sizeof(packet.data);
        packet.header.cksum = getChecksum(packet);
        ClientSend(sockfd, (struct sockaddr*)&address, addr_len, packet, retries);
        seq = (seq+1)%2;
        retries++;
        break;
    }
    

    // send zero-length packet to server to end connection according the description provided in the Lab manual
    Packet final;
    final.header.seq_ack=seq;
    final.header.len=0;
    final.header.cksum=getChecksum(final);
    retries = 0;
    ClientSend(sockfd,(struct sockaddr *)&address, addr_len, final, retries);
    retries++;


    // clean up
    close(fp);
    close(sockfd);
    return 0;
}
