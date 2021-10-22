#include "calculator.h"

double* sumar_1_svc(Operands* operands, struct svc_req* req) {
	static double result;	
	result = operands->op1 + operands->op2;	
	return &result;
}

double* restar_1_svc(Operands* operands, struct svc_req* req) {
	static double result;	
	result = operands->op1 - operands->op2;	
	return &result;
}

double* multiplicar_1_svc(Operands* operands, struct svc_req* req) {
	static double result;	
	result = operands->op1 * operands->op2;	
	return &result;
}

double* dividir_1_svc(Operands* operands, struct svc_req* req) {
	static double result;	
	result = operands->op1 / operands->op2;	
	return &result;
}
