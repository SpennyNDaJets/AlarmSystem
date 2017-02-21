// KeyPad Class

#ifndef KEYPAD_H
#define KEYPAD_H

#include "arduino.h"
#include "MyButton.h"

class KeyPad{
public:
	// constructor
	KeyPad();
	~KeyPad();

	// check if key has been pressed
	int checkKeyPress();

private:
	MyButton* check;
};

#endif