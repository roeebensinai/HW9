
#include "field.h"
#include "ip.h"
#include "port.h"
#include <iostream>
#include <cstring>

//-------------------------------------------------------------------------------------

Field::Field(String pattern, field_type type) { // Constructor
	this->pattern = pattern;
	this->type = type;
}

//-------------------------------------------------------------------------------------

Field::Field(String pattern) { // Constructor
	this->pattern = pattern;
	this->type = GENERIC;
}

//-------------------------------------------------------------------------------------

Field::~Field() { // Distructor
}

//-------------------------------------------------------------------------------------

field_type Field::get_type() const {
	return type;
}

//-------------------------------------------------------------------------------------

bool Field::set_value(String val) {
	if (type == PORT) {
		return ((Port*)this)->set_value(val);
	}
	if (type == IP) {
		return ((Ip*)this)->set_value(val);
	}
	return false;
}

//-------------------------------------------------------------------------------------

bool Field::match_value(String val) const {	
	if (type == PORT) {
		return ((Port*)this)->match_value(val);
	}
	if (type == IP) {
		return ((Ip*)this)->match_value(val);
	}
	return false;
}

//-------------------------------------------------------------------------------------

bool Field::match(String packet) {
	String* sub_packets;
	String* str_array;
	size_t num_of_sub_packets = 0;
	size_t num_of_str_array = 0 ;
	int rule_success_cnt = 0;
	packet.split(",", &sub_packets, &num_of_sub_packets); // Split the packet by ','
	if (num_of_sub_packets != 0) { // Valid packet
		for(int i = 0; i < (int)num_of_sub_packets; i++) {
			sub_packets[i].split("=", &str_array, &num_of_str_array); // Split command by '='
			if (num_of_str_array == 2) { // Check if command is valid
				if (pattern.trim().equals(str_array[0].trim())) { // Check if the current command name fits the rule name
					if(match_value(str_array[1].trim()) == true){ // The command fits the rule
						rule_success_cnt++;
					}
				}
				else {
					continue; // Current command name doesn't fit the rule name
				}
			}
			else {
				continue; // Current command is invalid
			}
			delete[] str_array; // Free current command memory
		}
		delete[] sub_packets; // Free packet memory
		if (rule_success_cnt == 1) { // Check if there is a command that fits the rule
			return true;
		}
		else {
			return false;
		}
	}
	else { // Invalid packet
		return false;
	}
}