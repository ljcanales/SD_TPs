/*standard symbols */
#include <unistd.h>  

/* sockets */
#include <netdb.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <arpa/inet.h>

/* strings / errors*/
#include <errno.h>
#include <stdio.h> 
#include <string.h> 

/* server parameters */
#define SERV_PORT       8080              /* port */ /*10.0.2.15*/
#define SERV_HOST_ADDR "10.0.2.15"     /* IP, only IPV4 support  */ 
#define BUF_SIZE        100               /* Buffer rx, tx max size  */
#define BACKLOG         5                 /* Max. client pending connections  */

int main(int argc, char* argv[]) {
    int sockfd, connfd ;  /* listening socket and connection socket file descriptors */
    unsigned int len;     /* length of client address */
    struct sockaddr_in servaddr, client;

    int  len_rx, len_tx = 0;  /* received and sent length, in bytes */
    char buff_rx[BUF_SIZE];   /* buffers for reception  */


    /* socket creation */
    sockfd = socket(AF_INET, SOCK_STREAM, 0); /*Dominio, tipo de socket, protocolo especificado*/
    if (sockfd == -1) {
        fprintf(stderr, "[SERVER-error]: socket creation failed. %d: %s \n", errno, strerror( errno )); /* se produccio un error en la creacion del socket*/
        return -1;
    } else {
        printf("[SERVER]: Socket successfully created..\n"); 
    }

    /* clear structure */
    memset(&servaddr, 0, sizeof(servaddr));

    /* assign IP, SERV_PORT, IPV4 */
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR); /* se define la direccion ip*/
    servaddr.sin_port        = htons(SERV_PORT);


    /* Bind socket --> se asigna la direccion y puerto*/
    if ((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) {
        fprintf(stderr, "[SERVER-error]: socket bind failed. %d: %s \n", errno, strerror( errno ));
        return -1;
    } else {
        printf("[SERVER] Socket successfully binded \n");
    }

    /* Listen */
    if ((listen(sockfd, BACKLOG)) != 0) {
        fprintf(stderr, "[SERVER-error]: socket listen failed. %d: %s \n", errno, strerror( errno ));
        return -1;
    } else {
        printf("[SERVER] Listening on SERV_PORT %d \n\n", ntohs(servaddr.sin_port) );
    }

    len = sizeof(client); 

      /* Accept the data from incoming sockets in a iterative way */
      while(1) {
        connfd = accept(sockfd, (struct sockaddr *)&client, &len);
        if (connfd < 0) {
            fprintf(stderr, "[SERVER-error]: connection not accepted. %d: %s \n", errno, strerror( errno ));
            return -1;
        }
        else {
            while(1) { /* read data from a client socket till it is closed */ 
                /* read client message, copy it into buffer */
                len_rx = recv(connfd, buff_rx, sizeof(buff_rx), 0);  

                if(len_rx == -1) {
                    fprintf(stderr, "[SERVER-error]: connfd cannot be read. %d: %s \n", errno, strerror( errno ));
                }
                else if(len_rx == 0) { /* if length is 0 client socket closed, then exit */
                    printf("[SERVER] Client socket closed \n\n");
                    close(connfd);
                    break; 
                } else {
                    printf("[SERVER] Message received: %s \n", buff_rx);
                    send(connfd, buff_rx, strlen(buff_rx), 0);
                }
            }
        }
    }
}
