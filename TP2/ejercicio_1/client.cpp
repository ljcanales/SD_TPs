#include <iostream>
#include "calculator.h"

using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 4) {
		cerr << "Uso: cliente_calculadora <server> <op1> <op2>" << endl;
		return 1;
	}
	char *server = argv[1];

	CLIENT *clnt = clnt_create(server, CALCULATOR, CALCULATOR_VER, "tcp");
	if (clnt == NULL) {
		cerr << "Error al crear un cliente de rpc" << endl;
		clnt_pcreateerror(server);
		exit(EXIT_FAILURE);
	}
	
	Operands operands;
	operands.op1 = atoi(argv[2]);
	operands.op2 = atoi(argv[3]);
	
	double* result;
	
	cout << "Procesando la suma de " << operands.op1 << " y " << operands.op2 << endl;
	result = sumar_1(&operands, clnt);
	if (result != NULL) {
		cout << *result << endl;
	} else {
		cerr << "Error!" << endl;
		clnt_perror(clnt, server);
	}
	
	cout << "Procesando la resta de " << operands.op1 << " y " << operands.op2 << endl;
	result = restar_1(&operands, clnt);
	if (result != NULL) {
		cout << *result << endl;
	} else {
		cerr << "Error!" << endl;
		clnt_perror(clnt, server);
	}
	
	cout << "Procesando la multiplicación de " << operands.op1 << " y " << operands.op2 << endl;
	result = multiplicar_1(&operands, clnt);
	if (result != NULL) {
		cout << *result << endl;
	} else {
		cerr << "Error!" << endl;
		clnt_perror(clnt, server);
	}
	
	cout << "Procesando la división de " << operands.op1 << " y " << operands.op2 << endl;
	result = dividir_1(&operands, clnt);
	if (result != NULL) {
		cout << *result << endl;
	} else {
		cerr << "Error!" << endl;
		clnt_perror(clnt, server);
	}
	
	exit(EXIT_SUCCESS);
}
