#include "ip.h"
#include <cstring>
#include <iostream>

Ip::Ip(String pattern): Field(pattern, IP) {
}

//-------------------------------------------------------------------------------------

bool Ip::set_value(String val) {	
	size_t num_of_substr = 0;
	String *ip_str;
	val.split("/", &ip_str, &num_of_substr);
	if (num_of_substr == 2) { // Valid IP rule
		int ip_int = ip_str[0].trim().to_integer(); // ip_int repressent IP as an integer
		int mask_int = ip_str[1].trim().to_integer(); // mask_int is the number of MSB to consider 
		delete[] ip_str;
		if((mask_int < 0) || (mask_int > 32)) {	// Check for invalid mask
			return false;
		}
		long long one = 1;
		long long full_musk = (one << 32) -1;// create 32 bits of '1'
		int low_musk = (int)(full_musk << (32 - mask_int)); //sets '1' to the number of MSB to consider, the rest '0'
		low = low_musk & ip_int; // sets '0' to the lower bits of the IP integer
		int high_musk = ~low_musk;
		high = high_musk | ip_int; // sets '1' to the lower bits of the IP integer
		return true; // if we get here we succesfully confirm the rule
	}
	else { //Invalid IP rule
		delete[] ip_str;// deallocate memory 
		return false;
	}
}

//-------------------------------------------------------------------------------------

bool Ip::match_value(String val) const {
	unsigned int val_ip = val.trim().to_integer();// gets Val's Ip field
	if((val_ip <= high) && (low <= val_ip)){ // Ip rule correctness validation 
		return true;
	}
	return false;
}
