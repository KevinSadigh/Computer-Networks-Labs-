#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

// server side
int main(int argc, char **argv) {
    char buffer[4]; // this is the buffer that will hold messages from client
    char response[4]; // this is the message that will be sent to client
    
    // address info for the server and client
    struct sockaddr_in server = {0};
    struct sockaddr_in from = {0};
    
    socklen_t s = sizeof(struct sockaddr_in);
    
    int socketFd = socket(AF_INET, SOCK_DGRAM, 0); // create the socket
    
    // setting up the servers server sock address
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(atoi(argv[1]));
    
    // bind the address of the server
    if(bind(socketFd, (struct sockaddr *) &server, sizeof(server)) < 0){
        // error 
        exit(0);
    }
    
    while(1){
        recvfrom(socketFd, buffer, sizeof(buffer), 0, (struct sockaddr*) &from, &s);
    
        if(strcmp(buffer, "ftp") == 0){
            strcpy(response, "yes");
        }else{
            strcpy(response, "no");
        }
        
        sendto(socketFd, response, sizeof(response), 0, (struct sockaddr*) &from, s);
    }
}
