#include "my_FS.h"
#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

int main(int argc, char const *argv[]) {
    if (argc < 3) {
		cerr << "Uso: ./client <server> [<get|realease> <string> | <state>]" << endl;
		exit(EXIT_SUCCESS);
	}

    const char *server = argv[1];
    const char *option = argv[2];

	CLIENT *clnt = clnt_create(server, MY_FS, MY_FS_VER, "tcp");
    if(clnt == NULL) {
		cerr << "Error al crear un cliente de rpc" << endl;
		clnt_pcreateerror(server);
		exit(EXIT_FAILURE);
	}

    char *str = (char*)argv[3];
    
    if(argc == 4 && strcmp(option,"get") == 0) {
        char** result = NULL;
        cout << "Nombre del archivo: " << str << endl;
        result = get_file_1(&str, clnt);
        if (result != NULL) {
            cout << *result << endl;
        } else {
            cerr << "Error!" << endl;
            clnt_perror(clnt, server);
        }
    } else if(argc == 4 && strcmp(option,"release")==0){
        int* result = NULL;
        cout << "Releasing file: " << str << endl;
        result = release_file_1(&str, clnt);
        cout << *result << endl;
    } else if(argc == 3 && strcmp(option,"state")==0){
        char** result = NULL;
        result = get_state_1(&str, clnt);
        if (result != NULL) {
            cout << *result << endl;
        } else {
            cerr << "Error!" << endl;
            clnt_perror(clnt, server);
        }
    }else {
        cerr << "Uso: ./client <server> <get|realease> <string> -------------" << endl;
    }    

}