#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <map>
#include <iostream>
#include <fstream>

#define FILES_DIRECTORY "./server_files/" // directorio base de archivos
#define MAX_CACHE 512000000 // 512MB

// server parameters
#define SERV_PORT 8080
#define BUF_SIZE 100
#define BACKLOG 5

using namespace std;

map<string, string> cache;
map<string, int> file_sizes;
int cache_used_size = 0;


char * get_file(string file_path);

int main(int argc, char const *argv[]) {
    
    int sockfd, connfd ;  /* listening socket and connection socket file descriptors */
    struct sockaddr_in servaddr, client;
    int len = sizeof(client);     /* length of client address */

    int  len_rx = 0;

    // SOCKET CREATION
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("[SERVER-error]: socket creation failed");
        exit(EXIT_FAILURE);
    } else {
        cout << endl << "[SERVER]: Socket successfully created.." << endl; 
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // SOCKET CONFIGURATION
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(SERV_PORT);

    if ((bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))) != 0) {
        perror("[SERVER-error]: socket bind failed");
        exit(EXIT_FAILURE);
    } else {
        cout << endl << "[SERVER] Socket successfully binded" << endl;
    }

    if ((listen(sockfd, BACKLOG)) != 0) {
        perror("[SERVER-error]: socket listen failed.");
        exit(EXIT_FAILURE);
    } else {
        cout << "[SERVER] Listening on IP " << inet_ntoa(servaddr.sin_addr) << endl;
        cout << "[SERVER] Listening on PORT " << SERV_PORT << endl;
    }

    while(1) {
        char buff_rx[BUF_SIZE] = "";

        if((connfd = accept(sockfd, (struct sockaddr *) &client, (socklen_t *) &len)) < 0) {
            perror("[SERVER-error]: connection not accepted.");
            exit(EXIT_FAILURE);
        } else {
            cout << "Dirección IP del cliente:" << inet_ntoa(client.sin_addr) << endl;
            while(1) {
                len_rx = recv(connfd, &buff_rx, sizeof(buff_rx), 0);

                if(len_rx == -1) {
                    perror("[SERVER-error]: connfd cannot be read.");
                }
                else if(len_rx == 0) { /* if length is 0 client socket closed, then exit */
                    cout << endl << "[SERVER] Client socket closed" << endl;
                    close(connfd);
                    break;
                } else {
                    cout << "[SERVER] Archivo solicitado: " << buff_rx << endl;
                    char *file_content = get_file(buff_rx);
                    send(connfd,file_content, strlen(file_content), 0);
                    close(connfd);
                    break;
                }
            }
        }
    }
}

char * get_file(string filename){
    string file_path = FILES_DIRECTORY;
    file_path += filename;
    char *file_content;
    cout<< " searching for: " + file_path << endl;
    // check if file in cache
    if(cache.find(filename) == cache.end()) {
        cout << " el archivo no se encuentra en cache " << endl;
        ifstream file(file_path, ios::in);
        if(file.is_open()) {
            cout << " el archivo se encuentra en directorio" << endl;
            file.seekg(0, ios::end);
            long size = file.tellg();
            file_content = new char[size];
            file.seekg(0, ios::beg);
            file.read(file_content, size);
            file.close();
            if(size < MAX_CACHE) {
                //agregar a cache
                cout << " verificando espacio en cache" << endl;
                while(cache_used_size + size > MAX_CACHE) {
                    string aux = cache.begin()->first;
                    cout << " eliminando de cache archivo: " << aux << "(" << file_sizes[aux] << " bytes)" << endl;
                    cache.erase(aux);
                    cache_used_size -= file_sizes[aux];
                    file_sizes.erase(aux);
                }
                cout << " agregando archivo a cache: "  << filename << "(" << size << " bytes)" << endl;
                cache[filename] = file_content;
                file_sizes[filename] = size;
                cache_used_size += size;
            }
        } else {
            cout <<" el archivo no se encuentra en directorio  "<< endl;
            return (char*)"FILE_NOT_FOUND";
        }
    } else {
        cout << " el archivo se encuentra en cache: "  << filename << "(" << file_sizes[filename] << " bytes)" << endl;
        file_content = new char[file_sizes[filename]];
        strcpy(file_content, cache[filename].c_str());
    }
    return file_content;
}
