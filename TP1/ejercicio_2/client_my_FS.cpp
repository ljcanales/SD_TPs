#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <iostream>
#include <fstream>

#define FILES_DIRECTORY "./client_files/"
#define BUFFER_SIZE 1024
#define ERROR_RESPUESTA "FILE_NOT_FOUND"
int respuesta = 0;
using namespace std;

int main(int argc, char const *argv[]) {
    if(argc != 4) {
        printf("\nUso:\t./client <SERVER_IP> <SERVER_PORT> <FILENAME>\n\n");
        exit(EXIT_SUCCESS);
    }
    char const *server_ip = argv[1], *filename = argv[3];
    int const server_port = atoi(argv[2]);

    int sockfd;
    struct sockaddr_in servaddr;

    // SOCKET CREATION
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("[CLIENT-error]: socket creation failed");
        exit(EXIT_FAILURE);
    } else {
        cout << endl << "[CLIENT]: Socket successfully created.." << endl; 
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // SOCKET CONFIGURATION
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(server_ip);
    servaddr.sin_port = htons(server_port);

    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) {
        perror("[CLIENT] Connection with the server failed");
        exit(EXIT_FAILURE);
    }
    cout << "[CLIENT] Connected to server" << endl;

    send(sockfd, filename, strlen(filename), 0);

    string file_path = FILES_DIRECTORY;
    file_path += filename;
    ofstream file;

    int total_size = 0;
    cout << "[CLIENT] Recibiendo... " << endl;
    while (1) {
        char buff_rx[BUFFER_SIZE] = "";
        respuesta = recv(sockfd, buff_rx, sizeof(buff_rx), 0);
        if(respuesta == -1) {
            perror("error");
        } else if(respuesta == 0) {
            cout << "[CLIENT] Fin recepción " << endl;
            break;
        } else {
            if(string(buff_rx) == ERROR_RESPUESTA)
                break;
            total_size += respuesta;
            if (!file.is_open()) {
                file.open(file_path);
                file << buff_rx;
            }   
        }
    }
    if(file.is_open()){
        file.close();
        cout << "Se guardo el archivo en: " << file_path << " (" << total_size << " bytes)" << endl;
    }

    close(sockfd);
}
