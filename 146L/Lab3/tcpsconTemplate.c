//COEN 146L : Lab3, step 3: concurrent TCP server that accepts and responds to multiple client connection requests, each requesting a file transfer
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//Define the number of clients/threads that can be served
#define N 100
int threadCount = 0;
pthread_t clients[N]; //declaring N threads

 //Declare socket and connection file descriptors.
int sockFD, connFD, rb, sin_size;
 //Declare receiving and sending buffers of size 1k bytes
char sbuf[1024], rbuf[1024];
 //Declare server address to which to bind for receiving messages and client address to fill in sending address
struct sockaddr_in servAddr, clienAddr;
//Connection handler (thread function) for servicing client requests for file transfer
void* connectionHandler(void* sock){
   //declare buffer holding the name of the file from client
   char data[1024];
   int rFP, read_bytes, write_bytes, sockFP;
   //Connection established, server begins to read and write to the connecting client
   sockFP = *(int *)sock;
   printf("Connection Established with client IP: %s and Port: %d\n", inet_ntoa(clienAddr.sin_addr), ntohs(clienAddr.sin_port));
   
   //receive name of the file from the client
   printf("reading from client...");
   rb = read(sockFP, data, sizeof(data));  
   //open file and send to client
   rFP = open(data, O_RDONLY);
   //read file and send to connection descriptor
   while((read_bytes = read(rFP, rbuf, sizeof(rbuf)))>0)
   {
     if((write_bytes = write(sockFP, rbuf, read_bytes)) == -1)
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
   pthread_exit(0);
}


int main(int argc, char *argv[]){
 int i;
 //Get from the command line, server IP, src and dst files.
 if (argc != 2){
	printf ("Usage: %s <port #> \n",argv[0]);
	exit(0);
 } 
 //Open a TCP socket, if successful, returns a descriptor
 if((sockFD = socket(AF_INET, SOCK_STREAM, 0)) < 0)
 {
   perror("Failure to setup an endpoint socket");
   exit(1);

 }

 //Setup the server address to bind using socket addressing structure
 servAddr.sin_family = AF_INET;
 servAddr.sin_port = htons(atoi(argv[1]));
 servAddr.sin_addr.s_addr = INADDR_ANY;


 //bind IP address and port for server endpoint socket
   if((bind(sockFD, (struct sockaddr *)&servAddr, sizeof(struct sockaddr))) < 0)
   {
      perror("Failure to bind server address to the endpoint socket");
      exit(1);
   }
   printf("Server waiting for client at port %s\n",argv[1]);


 // Server listening to the socket endpoint, and can queue 5 client requests
 printf("Server listening/waiting for client at port 5000\n");
 listen(sockFD, 5);
 sin_size = sizeof(struct sockaddr_in);
 
 while (1){
   //Server accepts the connection and call the connection handler
    if ((connFD = accept(sockFD, (struct sockaddr *)&clienAddr,
                        (socklen_t *)&sin_size)) < 0)
    {
      perror("Failure to accept connection to the client");
      exit(1);
    }

   
   if(pthread_create(&clients[threadCount], NULL, connectionHandler, (void*) &connFD) < 0){
      perror("Unable to create a thread");
      exit(0);
   }
   else 
      printf("Thread %d has been created to service client request\n",++threadCount);

   
 }
 for(i = 0; i < threadCount; i++){
      pthread_join(clients[i], NULL);
 }

 return 0;
}