// KeyPad Implementation 

#include "KeyPad.h"


// constructor
KeyPad::KeyPad(){
	check = new MyButton(0);
}

// deconstructor
KeyPad::~KeyPad(){
	delete check;
}

// check if key has been presses
int KeyPad::checkKeyPress(){

	// loop through columns and set each pin to input
	for (int c = 0; c < 3; c++) {
		check->setPin(c);

		// loop through rows and set each pin to output 5V
		for (int r = 0; r < 4; r++) {
			int pin2 = r + 3;
			digitalWrite(pin2, HIGH);

			// determine which button was pressed
			if (check->checkButtonEvent()){
				return c + 1 + 3 * r;
			}

		}
	}

	// if no button was pressed
	return 0;
}