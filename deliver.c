#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

// client side
int main(int argc, char **argv) {
    //struct sockaddr_in client = {0};
    //struct sockaddr_in server = {0};
    
    struct addrinfo hints, *serverip; //for server ip address 
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    int socketFd = socket(AF_INET, SOCK_DGRAM, 0); // create the socket
    
    char msg[] = "ftp";
    char response[4]; // has to be yes

    if (getaddrinfo(argv[1], argv[2], &hints, &serverip) != 0){
        printf("Getting host address failed\n");
        exit(0);
    }
    // do logic to see in file exists
    if(access(argv[4], F_OK) == 0){
        // send message 'ftp' to the server
        sendto(socketFd, msg, sizeof(msg), 0, serverip->ai_addr, serverip->ai_addrlen);
    }else{
        printf("not found!\n");
        exit(0);
    }
    
    recvfrom(socketFd, response, sizeof(response), 0, 0, 0); // get the response from the server
    
    if(strcmp(response, "yes") == 0){
        printf("A file transfer can start.\n");
        exit(0);
    }else{
        
        printf("%s this is where it is failing!\n", response);
        exit(0);
    }
    
}