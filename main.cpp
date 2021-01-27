
#include <iostream>
#include <cstring>
#include "ip.h"
#include "port.h"
extern int check_args(int, char**);
extern void parse_input(Field&);

int main(int argc, char** argv) {
	size_t size = 0;
	String* str_array;
	
	if (check_args(argc, argv) != 0) {
		return 1;
	}
	
	char *current_rule = argv[1];
	String rule(current_rule); // Define a new string for the current rule
	rule.split("=", &str_array, &size); // Will help us to check if the command is port / IP
	String rule_name(str_array[0].trim());
	String rule_val(str_array[1].trim());
	if((rule_name.equals("src-port")) || (rule_name.equals("dst-port"))) { // Check if the command is port
		Port port_setter(rule_name);
		port_setter.set_value(rule_val);
		parse_input(port_setter);
	}
	if ((rule_name.equals("src-ip")) || (rule_name.equals("dst-ip"))) { // Check if the command is IP
		Ip ip_setter(rule_name);	
		ip_setter.set_value(rule_val);
		parse_input(ip_setter);
	}
	delete[] str_array;
}
