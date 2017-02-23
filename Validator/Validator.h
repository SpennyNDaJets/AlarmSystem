// Validator class

#ifndef VALIDATOR_H
#define VALIDATOR_H


class Validator {
public:
	// constants
	const int star = 10;
	const int zero = 11;
	const int pound = 12;

	// default constructor
	Validator();

	// constructor with 4 inputs
	Validator(int f, int s, int t, int fo);

	// convert to 0 if zero key is pressed
	int convertZero(int digit);

	// reset if star was pressed
	void reset();

	//check if entered code was correct
	bool validateCode();

	// check if digit matches code and unlock if all digits entered followed by '#'
	bool checkCode(int digit);


private:
	int code[4];
	int count;
};

#endif