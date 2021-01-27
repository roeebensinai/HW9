#include "port.h"
#include <cstdlib>
#define MAX_NUM 65535

Port::Port(String pattern): Field(pattern, PORT) {
}

//----------------------------------------------------------------------------------------------------------

bool Port::set_value(String val){
	size_t num_of_substr = 0;
	String *port_str;

	val.split("-", &port_str, &num_of_substr);
	if (num_of_substr == 2) {
		range[0] = port_str[0].trim().to_integer();
		range[1] = port_str[1].trim().to_integer();
		delete[] port_str; // Free mem
		if (range[0] <= range[1]) {
			if ((range[0] <= MAX_NUM) && (0 <= range[0]) && (range[1] <= MAX_NUM) && (0 <= range[1])) { // Check if range is valid
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;// Invalid port range
		}
	}
	else {
		delete[] port_str;
		return false;
	}
}

//----------------------------------------------------------------------------------------------------------

bool Port::match_value(String val) const {
	int val_port = val.trim().to_integer();// Gets Val's port field
	if((val_port <= range[1]) && (range[0] <= val_port)){ // Port rule correctness validation 
		return true;
	}
	return false;
}