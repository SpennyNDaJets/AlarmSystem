// KeyPad Implementation 

#include "KeyPad.h"


// constructor
KeyPad::KeyPad(){
	check = new MyButton(0);
}

// destructor
KeyPad::~KeyPad() {
	delete check;
}

// check if key has been presses
int KeyPad::checkKeyPress(){

	// loop through columns and set each pin to input
	// cannot use pins 0 or 1
	for (int r = 0; r < 4; r++) {
		int output = r + 7;
		digitalWrite(output, HIGH);

		// loop through rows and set each pin to output 5V
		for (int c = 0; c < 3; c++) {
			int input = c + 4;
			check->setPin(input);

			// determine which button was pressed
			if (check->checkButtonEvent()){
				digitalWrite(output, LOW);
				return 1 + c + 3 * r;
			}
		}
		digitalWrite(output, LOW);
	}

	// if no button was pressed
	return 0;
}