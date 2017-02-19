// Button Class

#ifndef MYBUTTON_H
#define MYBUTTON_H

#include "arduino.h";
#include "EventTimer.h"

class MyButton {

public:
	MyButton(int pin);
	~MyButton();
	bool checkButtonEvent();
	void setPin(int pin);

private:
	int pinNum;
	int lastButtonState;
	EventTimer* debounce;
};

#endif