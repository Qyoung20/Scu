/* 
* Name: Quinton Young
* Date: 4/21/22 (the day you have lab)
* COEN 146L : Lab3, step 1: TCP client requesting a file transfer from the server.*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <arpa/inet.h>


int main(int argc, char *argv[]){
    //Get from the command line, server IP, src and dst files.
    if (argc != 5){
		printf ("Usage: %s <ip of server> <port #> <src_file> <dest_file>\n",argv[0]);
		exit(0);
    } 
    //Declare socket file descriptor and buffer
    int sockfd;
    char buf[10];

    //Declare server address to accept
    struct sockaddr_in servAddr;
    
   //Declare host
    struct hostnet *host;

    //get hostname
    host = (struct hostnet *) gethostbyname(argv[1]);

    //Open a socket, if successful, returns
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
      perror("Failure to setup endpoint");
      exit(1);
    }

    //Set the server address to send using socket addressing structure
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(atoi(argv[2]));
    servAddr.sin_addr.s_addr = inet_addr(argv[1]);
    //Connect to the server
    if(connect(sockfd, (struct sockaddr *)&servAddr, sizeof(struct sockaddr)) < 0){
      perror("Failure to connect to server");
      exit(1);
    }
    printf("[+]Connected to the server.\n");
    //Client sends the name of the file to retrieve from the server
    write(sockfd, argv[3], strlen(argv[3])+1);
    
    printf("Server: %s\n", buf);
    //Client begins to write and read from the server
    FILE *fp;
    size_t readFile;
    fp = fopen (argv[4], "w");
    while(1){
      readFile = read(sockfd, buf, 1024);
      if(readFile < 0)
      perror("read");

      fwrite(&buf, 1, readFile, fp);
      if(readFile == 0) 
      break;
    }
    fclose (fp);
    printf("%d\n", readFile);
    //Close socket descriptor
    
    close (sockfd);
    return 0;
}

