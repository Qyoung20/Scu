//COEN 146L : Lab3, step 1: TCP server that accepts a client connection for file transfer.
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <string.h>

//Declare socket file descriptor.
int sockfd, connfd, rb, sin_size;

//Declare receiving and sending buffers of size 10 bytes
char sbuf[1024], bbuf[1024];

//Declare server address to which to bind for receiving messages and client address to fill in sending address
struct sockaddr_in servAddr, clienAddr;


//Connection handler for servicing client request for file transfer
void* connectionHandler(void* sock){
   //declate buffer holding the name of the file from client
   char data[1024];
   int rFP, read_bytes, write_bytes,sockFP;
   //get the connection descriptor
   sockFP = *(int *)sock;
   //Connection established, server begins to read and write to the connecting client
   printf("Connection Established with client IP: %s and Port: %d\n", inet_ntoa(clienAddr.sin_addr), ntohs(clienAddr.sin_port));
	//receive name of the file from the client
	printf("reading from client...");
   rb = read(sockFP, data, sizeof(data));
   
   data[rb] = '\0';
   printf("Client sent: %s\n", data);
   //open file and send to client
   rFP = open(data, O_RDONLY);
   //read file and send to connection descriptor
   while((read_bytes = read(rFP, bbuf, sizeof(bbuf))) > 0)
   {
      if ((write_bytes = write(sockFP, bbuf, read_bytes)) == -1)
      {
         perror("[-]Error in sending file.");
         exit(1);
      }
      if(write_bytes != read_bytes)
      {
         printf("write bytes(%d) different from read bytes(%d):\n ",write_bytes, read_bytes);
         return 0;
      }
   }
   printf("File transfer complete\n");
   
   //close file
   close(rFP);

   //Close connection descriptor
   close(sockFP);
   return 0;
}


int main(int argc, char *argv[]){
   struct sockaddr_in servAddr, clienAddr;
 //Get from the command line, server IP, src and dst files.
   if (argc != 2){
	   printf ("Usage: %s <port #> \n",argv[0]);
	   exit(0);
   } 
 //Open a TCP socket, if successful, returns a descriptor
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
   {
      perror("Failure to setup an endpoint socket");
      exit(1);
   }
 //Setup the server address to bind using socket addressing structure
   servAddr.sin_family = AF_INET;
   servAddr.sin_port = htons(atoi(argv[1]));
   servAddr.sin_addr.s_addr = INADDR_ANY;
 //bind IP address and port for server endpoint socket 
   if ((bind(sockfd, (struct sockaddr *)&servAddr, sizeof(struct sockaddr))) < 0){
      perror("Failure to bind server address to the endpoint socket");
      exit(1);
   }
   printf("Server waiting for client at port %s\n",argv[1]);
 // Server listening to the socket endpoint, and can queue 5 client requests
 printf("Server listening/waiting for client at port %d\n", atoi(argv[1]));
   listen(sockfd, 5);
   sin_size = sizeof(struct sockaddr_in);

   //Server accepts the connection and call the connection handler
   if ((connfd = accept(sockfd, (struct sockaddr *)&clienAddr,
                        (socklen_t *)&sin_size)) < 0)
   {
      perror("Failure to accept connection to the client");
      exit(1);
   }
   connectionHandler((void *)&connfd);

   //close socket descriptor
   close(sockfd);
   return 0;
}