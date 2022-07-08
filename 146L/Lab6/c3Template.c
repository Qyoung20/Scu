//COEN 146L: Lab6, UDP client with packets that have checksum, sequence number, acknowledgement number, and timer
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>

#define PBADCKSUM 5
#define PLOSTMSG 5











//Declare a Header structure that holds, sequence/ acknowledgement number, checksum, and length of a packet
typedef struct {
    int seq_ack;
    int len;
    int cksum;
} Header;

//Declare a packet structure that holds data and header
typedef struct {
    Header header;
    char data[10];
} Packet;

//Calculate the Checksum
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

//Print received packet
void logPacket(Packet packet) {
    printf("Packet{ header: { seq_ack: %d, len: %d, cksum: %d }, data: \"",
           packet.header.seq_ack,
           packet.header.len,
           packet.header.cksum);
    fwrite(packet.data, (size_t)packet.header.len, 1, stdout);
    printf("\" }\n");
}

//client sending packet with checksum and sequence number, waits for acknowledgement, and sets up a time
void ClientSend(int sockfd, const struct sockaddr *address, socklen_t addrlen, Packet packet, unsigned retries) {
    int attempts = 0;
    while (attempts < retries) {
        // calculate the checksum
        int chksum = getChecksum(packet);

        // log what is being sent
        printf("Created: ");
        logPacket(packet);

        // Simulate lost packet.
        if (rand() % PLOSTMSG == 0) {
            printf("Dropping packet\n");
        }
        // if packet's not lost, we should send it to the server
        else {
            sendto(sockfd, &packet, sizeof(packet), 0, address, addrlen);
        }
        
        // wait until an ACK is received or timeout using select statement      
        // local variables needed
        struct  timeval tv; // timer
        tv.tv_sec = 1;
        tv.tv_usec = 0;
        int rv;     // select returned value

        // set up reads file descriptor at the beginning of the function to be checked for being ready to read
        fd_set  readfds;
        fcntl (sockfd, F_SETFL, O_NONBLOCK);

        // start before calling select
        FD_ZERO (&readfds); //initializes readfds to have zero bits
        FD_SET (sockfd, &readfds); //sets readfds bit 
        rv = select(sockfd + 1, &readfds, NULL, NULL, &tv);
        //call select
        Packet recvpacket;
         if(rv == 0){ // timeout, no data
            printf("Timed out\n");
            attempts++;
        }
        else if(rv == 1){ // there is data to be received
            recvfrom(sockfd, &recvpacket, sizeof(recvpacket), 0, address, &addrlen);
            // log what was received
            printf("Received ACK %d, checksum %d - ", recvpacket.header.seq_ack, recvpacket.header.cksum);
            // validate the ACK
            if (recvpacket.header.cksum != getChecksum(recvpacket)) {
                // bad checksum, resend packet
                printf("Bad checksum, expected %d\n", getChecksum(recvpacket));
            }
            else if (recvpacket.header.seq_ack != packet.header.seq_ack) {
                // incorrect sequence number, resend packet with correct sequence number
                printf("Bad seqnum, expected %d\n", packet.header.seq_ack);
            }
            else {
                // good ACK, we're done
                printf("Good ACK\n");
                break;
            }
        }
    }
    if (attempts == 3){
        puts("Timed out after 3 tries");
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    //Get from the command line, server IP, Port and src file
    if (argc != 4) {
        printf("Usage: %s <ip> <port> <srcfile>\n", argv[0]);
        exit(0);
    }
    
    //Declare socket file descriptor.
    int sockfd; 
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Failure to setup an endpoint socket");
        exit(1);
    }

    //Declare server address to connect to
    struct sockaddr_in servAddr;
    struct hostent *host;
    memset(&servAddr, 0, sizeof(servAddr));
    host = (struct hostent *) gethostbyname(argv[1]);
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(atoi(argv[2]));
    servAddr.sin_addr = *((struct in_addr *)host->h_addr);
    ///Set the server address to send using socket addressing structure
    
    //initialize servAddr structure


    //Open file using argv[3]
    int fp = open(argv[3], O_RDWR);
    if(fp < 0){
    	perror("Failed to open file\n");
	    exit(1);
    }

    //Send file contents to server packet by packet
    int seq = 0;
    socklen_t addr_len = sizeof(servAddr);
    Packet packet;
    int bytes;
    while((bytes = read(fp, packet.data, sizeof(packet.data))) > 0){
    	//assign seq and checksum to packet and send
        packet.header.seq_ack=seq;
    	packet.header.len=bytes;
    	packet.header.cksum=getChecksum(packet);
    	ClientSend(sockfd,(struct sockaddr *)&servAddr,addr_len, packet, 3); //retries = 0
    	seq=(seq+1)%2;
    }

    //Send zero-length packet to server to end connection
    Packet final;
    final.header.seq_ack=seq;
    final.header.len=0;
    final.header.cksum=getChecksum(final);
    ClientSend(sockfd,(struct sockaddr *)&servAddr,addr_len,final, 0);
    
	//Close file and socket
    close(fp);
    close(sockfd);
    return 0;
}
