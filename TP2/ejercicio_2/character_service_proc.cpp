#include "character_service.h"
#include <string>
#include <sstream>

using namespace std;

int* cant_carac_e_1_svc(char **str, struct svc_req* req) {
	static int length;
	length = string(*str).length();
	return &length;
}

int* cant_carac_se_1_svc(char **str, struct svc_req* req) {
	static int count;
    count = 0;

	for(char c : string(*str))
		if(c != ' ')
			count++;

	return &count;
}

int* cant_palabras_1_svc(char **str, struct svc_req* req) {
    static int count;
	count = 0;
	
    string word;
	string s = string(*str);
    stringstream words(s);
 
    while(words >> word)
		count++;

	return &count;
}
