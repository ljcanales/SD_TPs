#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <unistd.h>

#define SERVER_ADDRESS  "10.0.2.15"     /* server IP */
#define PORT            8080 

/* Test sequences */
int  respuesta= 0;
char buf_tx[100];
char buf_rx[100];   /* receive buffer */

/* This clients connects, sends a text and disconnects */
int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("\nUso:\t./cliente <mensaje>\n\n");
        exit(EXIT_SUCCESS);
    }
    strcat(buf_tx, argv[1]);
    int sockfd;
    struct sockaddr_in servaddr;

    /* Socket creation */
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) {
        printf("[CLIENT] socket creation failed...\n");
        return -1;
    } else {
        printf("[CLIENT] Socket successfully created..\n");
    }

    memset(&servaddr, 0, sizeof(servaddr));

    /* assign IP, PORT */
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
    servaddr.sin_port = htons(PORT);

    /* try to connect the client socket to server socket */
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) {
        printf("[CLIENT] Connection with the server failed...\n");
        return -1;
    }

    printf("[CLIENT] Connected to the server..\n");

    /* send test sequences*/
    send(sockfd, buf_tx, sizeof(buf_tx), 0);
    respuesta =  recv(sockfd, buf_rx, sizeof(buf_rx), 0);
    if(respuesta == -1) {
        printf("error");
    } else if(respuesta == 0) { /* if length is 0 client socket closed, then exit */
        printf("[respuesta  ]: 0 \n\n");
    } else {
        printf("[CLIENT] Message received: %s \n", buf_rx);
    }
    /*comprobar lo de arriba*/

    /* close client socket */
    printf("[CLIENT] Closing socket\n\n");
    close(sockfd);
}
