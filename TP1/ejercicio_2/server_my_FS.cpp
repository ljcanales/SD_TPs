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

#define FILES_DIRECTORY "./files/" // directorio base de archivos
#define MAX_CACHE 512000000 // 512MB

using namespace std;

map<string, string> cache;
map<string, int> file_sizes;
int cache_usage_size = 0;

int main(int argc, char const *argv[]) {
    string file_path = "./files/test.txt";
    
    ifstream file(file_path, ios::in);
    if(file.is_open()) {
        file.seekg(0, ios::end);
        long size = file.tellg();
        char *contents = new char[size];
        file.seekg(0, ios::beg);
        file.read(contents, size);
        file.close();

        cout << endl << size << endl;
        cout << endl << contents << endl;
        
        delete [] contents;
    }
    
    file.close();

    // crear y configurar socket

    // escuchar clientes

        // leer archivo

        // if file_size mayor a MAX_CACHE
            // no guardar en cache, solo pasar por mensaje

        // else 
            // verificar que quede espacio en cache y guardarlo
            // si no hay espacio quitar archivos de la cache hasta que entre el nuevo

}

