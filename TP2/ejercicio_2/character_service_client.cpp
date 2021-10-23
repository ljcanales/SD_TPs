#include "character_service.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    if (argc != 3) {
		cerr << "Uso: ./client <server> <string>" << endl;
		exit(EXIT_SUCCESS);
	}

    const char *server = argv[1];

	CLIENT *clnt = clnt_create(server, CHARACTER_SERVICE, CHARACTER_SERVICE_VER, "tcp");
    if(clnt == NULL) {
		cerr << "Error al crear un cliente de rpc" << endl;
		clnt_pcreateerror(server);
		exit(EXIT_FAILURE);
	}

    char *str = (char*)argv[2];
    int* result = 0;

    cout << "Procesando longitud CON espacios de " << str << endl;
	result = cant_carac_e_1(&str, clnt);
	if (result != NULL) {
		cout << *result << endl;
	} else {
		cerr << "Error!" << endl;
		clnt_perror(clnt, server);
	}

    cout << "Procesando longitud SIN espacios de " << str << endl;
	result = cant_carac_se_1(&str, clnt);
	if (result != NULL) {
		cout << *result << endl;
	} else {
		cerr << "Error!" << endl;
		clnt_perror(clnt, server);
	}

    cout << "Procesando cantidad de palabras de " << str << endl;
	result = cant_palabras_1(&str, clnt);
	if (result != NULL) {
		cout << *result << endl;
	} else {
		cerr << "Error!" << endl;
		clnt_perror(clnt, server);
	}

    exit(EXIT_SUCCESS);

}
