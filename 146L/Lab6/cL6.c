
#include <arpa/inet.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>
#include <netdb.h>
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

// only get 3 retries for each packet before we back out
#define TRIES 3

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

void logPacket(Packet packet) {
    printf("Packet{ header: { seq_ack: %d, len: %d, cksum: %d }, data: \"",
           packet.header.seq_ack,
           packet.header.len,
           packet.header.cksum);
    fwrite(packet.data, (size_t)packet.header.len, 1, stdout);
    printf("\" }\n");
}

void ClientSend(int sockfd, const struct sockaddr *address, socklen_t addrlen, Packet packet, unsigned retries) {
    int attempts = 0;
    while (attempts < retries) {
        // calculate the checksum
        //******STUDENT WORK******
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
            //******STUDENT WORK******
            sendto(sockfd, &packet, sizeof(packet), 0, address, addrlen);
        }

        // wait until either a packet is received or timeout, i.e using the select statement
        struct timeval tv;
        tv.tv_sec = 1;
        tv.tv_usec = 0;
        fd_set readfds;
        //******STUDENT WORK******
        int rv;
        fcntl(sockfd, F_SETFL, O_NONBLOCK); // open our file descriptor
        FD_ZERO(&readfds); // initializes the file descriptor set fdset to have zero bits for all file descriptors
        FD_SET(sockfd, &readfds); // sets the bit for the file descriptor fd in the file descriptor set fdset.
        rv = select(sockfd + 1, &readfds, NULL, NULL, &tv);
    
        // receive an ACK from the server
        Packet recvpacket;
        //******STUDENT WORK******
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
    if (attempts == TRIES){
        puts("Timed out after 3 tries");
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    // check arguments
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <ip> <port> <infile>\n", argv[0]);
        return 1;
    }

    // seed the RNG
    srand((unsigned)time(NULL));

    // create and configure the socket
    //******STUDENT WORK******
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Failure to setup an endpoint socket");
        exit(1);
    }
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));

    // initialize the server address structure
    //******STUDENT WORK******
    socklen_t addr_len = sizeof(address);
    struct hostent *host;
    host = (struct hostent *) gethostbyname(argv[1]);
    address.sin_family = AF_INET;
    address.sin_port = htons(atoi(argv[2]));
    address.sin_addr = *((struct in_addr *)host->h_addr);

    // open file
    int fp = open(argv[3], O_RDWR);
    if(fp < 0){
        perror("fopen");
        return 1;
    }

    // send file contents to server
    Packet packet;
    //******STUDENT WORK******
    int seqnum = 0;
    while(read(fp, packet.data, sizeof(packet.data)) > 0){
        packet.header.seq_ack = seqnum;
        packet.header.len = strlen(packet.data);
        packet.header.cksum = getChecksum(packet);
        ClientSend(sockfd, (struct sockaddr *)&address, addr_len, packet, TRIES);
        seqnum = (seqnum + 1) % 2;
    }

    // send zero-length packet to server to end connection according the description provided in the Lab manual
    //******STUDENT WORK******
    Packet zero_length;
    zero_length.header.seq_ack = seqnum;
    zero_length.header.len = 0;
    zero_length.header.cksum = getChecksum(zero_length);
    ClientSend(sockfd, (struct sockaddr *)&address, addr_len, zero_length, TRIES);

    // clean up
    //******STUDENT WORK******
    close(fp);
    close(sockfd);
    return 0;
}