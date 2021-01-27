#include <iostream>
#include <cstring>
#include "string.h"
#include "ip.h" 
#define ERROR 1
#define FIRST 0
#define SECOND 1
#define THIRD 2
#define FOURTH 3
# define MAX_SEG 255

using namespace std;

//-------------------------------------------------------------------------------------

String::String() { // Constructor that initiates an empty string
	data = NULL;
	length = 0;
}

//-------------------------------------------------------------------------------------

String::String(const String &str) { // Copy constructor that initiates string from other string
	if (str.length == 0) { // Check for empty string
		data = NULL;
		length = 0;
		return;
	}
	else { // String is valid
		length = str.length; // Initialize the string length
		data = new char[length + 1]; // Allocate memory
		if (data == NULL) {
			return;
		}
		else { // Clone string
			strcpy(data, str.data);
		}
	}
}

//-------------------------------------------------------------------------------------

String::String(const char *str) { // Constructor that initiates a string from char array
	if (str == NULL) { // Check if str is invalid
		data = NULL;
		length = 0;
		return;
	}
	else { // String is valid
		length = strlen(str); // Get string length
		data = new char[length + 1]; // Allocate memory
		if (data == NULL) { // Memory allocation failed
			length = 0;
			return;
		}
		else { // Clone string
			strcpy(data, str);
		}
	}
}

//-------------------------------------------------------------------------------------


String::~String() { // Distructor
	if (data == NULL) {
		return; // No memory to free
	}
	else {
		delete[] data; // Free memory
	}
}

//-------------------------------------------------------------------------------------


String& String::operator=(const String &rhs) { // Operator that changes this from String
	if (data != NULL) { // Check if current string is not empty
		delete[] data; // Free current string
	}
	if (rhs.length == 0) { // If rhs string is empty
		length = 0;
		data = NULL;
		return *this;
	}
	length = rhs.length; // Set current length to rhs length
	data = new char[length + 1]; // Allocate memory
	
	if (data == NULL) { // Memory allocation failed
		length = 0;
		return *this;
	}
	else { // Clone string
		strcpy(data, rhs.data);
	}
	return *this;
}

//-------------------------------------------------------------------------------------

String& String::operator=(const char *str) { // Operator that changes this from char array
	
	if (str == NULL) { // Check if str is invalid
		length = 0;
		data = NULL;
		return *this;
	}
	else { // Str is valid
		if (data != NULL) { // Check if current string is not empty
			delete[] data; // Free current string
		}
		length = strlen(str); // Set current length to str length
		if (length == 0) { // If str is an empty string
			data = NULL;
			return *this;
		}
		data = new char[length + 1]; // Allocate memory
		if (data == NULL) { // Memory allocation failed
			length = 0;
			return *this;
		}
		else { // Clone string
			strcpy(data, str);
		}
		return *this;
	}
}

//-------------------------------------------------------------------------------------

bool String::equals(const String &rhs) const { // Method that returns true iff the contents of this equals to the contents of rhs
	if ((length == rhs.length) && (strcmp(data, rhs.data) == 0)) { // Compare content and length of strings
		return true;
	}
	else {
		return false;
	}
}

//-------------------------------------------------------------------------------------

bool String::equals(const char *rhs) const { // Method that returns true iff the contents of this equals to rhs
	if ((length == strlen(rhs)) && (strcmp(data, rhs) == 0)) { // Compare content and length of strings
		return true;
	}
	else {
		return false;
	}
}

//-------------------------------------------------------------------------------------

int count_substr(const char *copy_current_data, int copy_current_data_len, const char *delimiters) { // Count number of sub strings
	int num_of_delimiter = 0;
	if (delimiters == NULL) {
		return 1;
	}
	else {
		int length_of_delimiter = strlen(delimiters);
		for (int i = 0; i < copy_current_data_len - 1; i++) { 
			for (int j = 0; j < length_of_delimiter; j++) {
				if (copy_current_data[i] == delimiters[j]) {
					num_of_delimiter++;
					continue;
				}
			}
		}
		return (num_of_delimiter + 1); // Number of substrings is greater by 1 than number of delimiters
	}
}

//-------------------------------------------------------------------------------------

void String::split(const char *delimiters, String **output, size_t *size) const { // Method that splits this to several sub-strings according to delimiters
	char copy_current_data[length + 1] = {0};
	strncpy(copy_current_data, data, length);
	int length_of_delimiter = 0;
	if (delimiters != NULL) {
		length_of_delimiter = strlen(delimiters);
	}
	copy_current_data[length] = '\0'; // copy_current_data is the same string with '\0' in the end	
	*size = count_substr(copy_current_data, length + 1, delimiters); 
	if (output != NULL) {
		*output = new String[*size]; // Allocate memory for string array
		for (int i = 0; i < (int)length; i++) {
			for (int j = 0; j < length_of_delimiter; j++) {
				if (copy_current_data[i] == delimiters[j]) {
					copy_current_data[i] = '\0'; // Insert '\0' instead of each delimiter
				}
			}
		}
		int i = 0;
		int j = 0;
		int counter = 0;
		for (counter = 0; counter < (int)(*size); counter++) { // Initialize each string of output
			while ((counter == 0) && (copy_current_data[i] == '\0') && (i < (int)length + 1)) { // In case of delimiter in the begining
				i++;
				j++;
			}
			while ((copy_current_data[i] != '\0') && (i < (int)length + 1)) {
				i++;
			}
			(*output)[counter] = String(&copy_current_data[j]);
			j = i;
			while (((copy_current_data[i]) == '\0') && (i < (int)length + 1)) { // In case of raw of delimiters
				i++;
				j++;
			}
		}
	}
}

//-------------------------------------------------------------------------------------

String String::trim() const { // Remove any leading or trailing white-spaces
	if (data == NULL) {
		return String();
	}
	int copy_length = 0;
	for (int i = 0; i < (int)length; i++) { // Initializing an helper array
		if (data[i] != ' '){
			copy_length++;
		}
	}
	char data_copy[copy_length + 1];
	data_copy[copy_length] = '\0';
	int copy_index = 0;
	int data_index = 0;
	while (data[data_index] == ' ') {
		data_index++;
	}
	while (data[data_index] != ' ') {
		if (data[data_index] == '\0') {
			break;
		}
		else {
			data_copy[copy_index] = data[data_index];
			copy_index++;
			data_index++;
		}
	}
	return String(data_copy);
}

//-------------------------------------------------------------------------------------

int String::to_integer() const{ // Try to convert this-data to an integer
	int number_converted = 0;
	String* str_array_pt = NULL; // Use as argument for split
	size_t str_array_size = 0; // Use as argument for split
	int num_of_ip_elems = SEGMENTS;
	split(".", &str_array_pt, &str_array_size);// Use of that method is common with IP
	if((int)str_array_size != num_of_ip_elems){ // Any cases which are not IP
		number_converted = atoi(data);
		delete[] str_array_pt; // Free allocated memory
		return number_converted;
	}
	else{ // Case  of IP, 4 numbers
		int first_ip, second_ip, third_ip, fourth_ip;
		first_ip = str_array_pt[FIRST].trim().to_integer();
		second_ip = str_array_pt[SECOND].trim().to_integer();
		third_ip = str_array_pt[THIRD].trim().to_integer();
		fourth_ip = str_array_pt[FOURTH].trim().to_integer();
		if((first_ip > MAX_SEG)  || (first_ip < 0)  || // Check for invalid ip's
		   (second_ip > MAX_SEG) || (second_ip < 0) ||
		   (third_ip > MAX_SEG)  || (third_ip < 0)  ||
		   (fourth_ip > MAX_SEG) || (fourth_ip < 0)) {
			delete[] str_array_pt;
			return 0; // Error
		}
		else{
			number_converted = (first_ip << 24) | (second_ip << 16) | (third_ip << 8) | (fourth_ip);
			delete[] str_array_pt;
			return number_converted;
		}
	}
} 
