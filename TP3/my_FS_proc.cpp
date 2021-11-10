#include <fstream>
#include <map>
#include <string>
#include <semaphore.h>
#include <iostream>
#include "my_FS.h"

#define FILES_DIRECTORY "./server_files/" // directorio base de archivos
#define MAX_CACHE 512000000 // 512MB

using namespace std;

// cache
map<string, string> cache;
map<string, int> file_sizes;
int cache_used_size = 0;

// semaphore
map<string, sem_t> semaphores;

char** get_file_1_svc(char **str, struct svc_req* req) {
    static char *file_content = NULL;

    string filename = string(*str);
    string file_path = FILES_DIRECTORY;
    file_path += filename;

    if(semaphores.find(filename) == semaphores.end()) {
        sem_t mutex;
        sem_init(&mutex, 0, 1);
        semaphores[filename] = mutex;
        
    }

    sem_wait(&semaphores[filename]);

    cout << " searching for: " + file_path << endl;
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
            //return (char*)"FILE_NOT_FOUND";
            file_content = "FILE_NOT_FOUND";
            sem_destroy(&semaphores[filename]);
            semaphores.erase(filename);
        }
    } else {
        cout << " el archivo se encuentra en cache: "  << filename << "(" << file_sizes[filename] << " bytes)" << endl;
        file_content = new char[file_sizes[filename]];
        strcpy(file_content, cache[filename].c_str());
    }
    return &file_content;

}


int* release_file_1_svc(char **str, struct svc_req* req) {
    static int number;
    int var;
    string filename = string(*str);
    number = 0;
    
    if(semaphores.find(filename) != semaphores.end()) {
        sem_getvalue(&semaphores[filename],&var);
        if(var < 1) {
            sem_post(&semaphores[filename]);
            number = 1;
        }
    }
    return &number;
}

char** get_state_1_svc(void *args, struct svc_req* req) {
    static char *result;
    string state_info = string("");

    auto iter = semaphores.begin();
    state_info += "lock : estado : cantidad de clientes en esperando" ;
    state_info += "\n";
    while (iter != semaphores.end()) {
        state_info += iter->first;
        state_info += " : ";
        int cant;
        sem_getvalue(&iter->second, &cant);

        state_info += cant <= 0 ? "concedido" : "libre";
        state_info += " : ";
        if((cant >= 0)) {
            cant = 0;
        }else if (cant < 0)
        {
            cant = cant*(-1)+1;
        }
        state_info += to_string(cant);
        state_info += "\n";
        ++iter;
    }
    
    result = new char[state_info.size()];
    strcpy(result, state_info.c_str());
    return &result;
}
