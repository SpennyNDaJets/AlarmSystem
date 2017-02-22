// validator class

#ifndef VALIDATOR_H
#define VALIDATOR_H

#include "arduino.h"
#include "KeyPad.h"


class Validator {
public:
	Validator();
	Validator(int f, int s, int t, int f);
	~Validator();
	bool checkDigit(int position, int digit);
	bool unlock();

private:
	int[]* code;
};

#endif