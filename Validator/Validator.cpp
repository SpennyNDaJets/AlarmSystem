// Validator Implementation

#include "Validator.h"
#include "arduino.h"

// default constructor
Validator::Validator() {
	for (int i = 0; i < 4; i++){
		code[i] = 0;
	}
	count = 0;
}

// constructor with 4 ints
Validator::Validator(int f, int s, int t, int fo) {
	code[0] = f;
	code[1] = s;
	code[2]	= t;
	code[3] = fo;
	count = 0;
}

// convert to 0 if zero key is pressed
int Validator::convertZero(int digit) {
	if (digit == ZRO)
		return 0;
	else
		return digit;
}

// reset if '*' was pressed
void Validator::reset() {
	count = 0;
}

// check if entered code was correct
bool Validator::validateCode() {
	if (count == 4) {
		count = 0;
		return true;
	}
	else {
		count = 0;
		return false;
	}
}


// check if digit matches code and unlock if all digits entered followed by '#'
bool Validator::checkCode(int digit){
	// if nothing is pressed
	if (digit == 0) {
		return false;
	}
	// convert if 0
	int enter = convertZero(digit);

	// check '*'
	if (enter == STAR){

		reset();
		return false;
	}

	// validate code if '#'
	else if (enter == POUND){
		return validateCode();
	}

	// code is wrong if counter is less than 0 or greater than 3
	else if ((count < 0) || (count > 3)) {
		return false;
	}
	
	// code is wrong and set counter to -1
	else if (code[count] != enter) {
		count = -1;
		return false;
	}

	// check if button matches next digit of code
	else if (code[count] == enter){
		count ++;
		return false;
	}
}