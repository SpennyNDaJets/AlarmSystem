#include "MyButton.h"
#include "EventTimer.h"
#include "KeyPad.h"
#include "Validator.h"

// arduino pin references
int col1 = 4;
int col2 = 5;
int col3 = 6;
int row1 = 7;
int row2 = 8;
int row3 = 11;
int row4 = 10;
int redLed = 2; //also the pin for photo resistor LED
int greenLed = 3;
int on = 13;
int photoComp = 12;
int piezo = 9;
// solonoid is on pin A3
//white LED for photosensor is on pin A4
// Hall effect sensor is on pin A5

// state constants
int currentState = 0;    // inital state is door locked and system disengaged
int lockDis = 0;         // door locked and system disengaged
int unlockDis = 1;       // door unlocked and system disengaged
int armed = 2;           // system armed
int alarm = 3;           // alarm state
int openDoor = 4;        // door is open

// button, keypad, validator, and timer
MyButton onButton(on);
EventTimer solonoidTimer;
EventTimer flash;
KeyPad lock;
Validator code(6,9,6,9);

#define OFF 0
#define ON  1
int state = OFF;

void setup() {
  Serial.begin(9600);
  //columns
  pinMode(col1, INPUT);
  pinMode(col2, INPUT);
  pinMode(col3, INPUT);
  //rows
  pinMode(row1, INPUT);
  pinMode(row2, INPUT);
  pinMode(row3, INPUT);
  pinMode(row4, INPUT);
  //various lights and 
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(on, INPUT);
  pinMode(photoComp, INPUT);
  
  //Hall effect Sensor
  pinMode(A5, INPUT);

  //white LED for photosenser
  pinMode(A4, OUTPUT);

  //solonoid
  pinMode(A3, OUTPUT);

  //setup piezo
    cli();
  
  //Timer1 for tones
  TCCR1A = 0x00;                    //CTC mode: determine TOP
  TCCR1B = 0x0A;                    // pre-scaler of 8
  DDRB |= 0x02;                

  sei();

  
  flash.start(1);                   //start timer to get running
  digitalWrite(greenLed, HIGH);     //system disarmed to start
  Serial.println("Beginning");
}


//unlock door
void unlock() {
    digitalWrite(redLed, LOW);      //turn off red LED
    digitalWrite(greenLed, HIGH);   //turn on green LED
    digitalWrite(A4, LOW);          //turn off white LED
    digitalWrite(piezo, LOW);       //turn off piezo
    solonoidTimer.start(1000);      //allow solonoid to unlock door for 1 sec
    digitalWrite(A3, HIGH);         // engage solonoid to unlock door
    currentState = unlockDis;       //change state
}

// sound the alarm
void soundPiezo(){
  if(state == OFF){
      TCCR1A |= (1 << COM1A0);       //enable toggling of pin 9 on rollover
      state = ON;
    }
    else{
      TCCR1A &= ~(1 << COM1A0);      //disable pin 9
      state = OFF;
    }
}


//flash the red LED
void flashRedLed() {
  // flash red LED once a second
    if (digitalRead(redLed) == HIGH && flash.checkExpired()) {
        flash.start(500);
        digitalWrite(redLed, LOW);      //turn on red LED if off
    }
    else if (flash.checkExpired()){
      flash.start(500);
      digitalWrite(redLed, HIGH);      //turn off red LED if on
    }
}

// arm the alarm system
void armSystem() {
    digitalWrite(redLed, HIGH);     //turn on red LED
    digitalWrite(greenLed, LOW);    //turn off green LED
    digitalWrite(A4, HIGH);         //turn on white LED for photsensor
    currentState = armed;           //change state
    Serial.println("System armed");
}

void loop() {

  // arm system
  if (currentState == lockDis && onButton.checkButtonEvent())
  {
    armSystem();
  }

  // unarm system
  int keyPress = lock.checkKeyPress();
  if ((currentState == armed || currentState == alarm)
    && code.checkCode(keyPress)) {
    unlock();                            //unlock door
    Serial.println("Door Unlocked, System Disarmed");
  }


  //enter the door open state if the Hall effect sensor stops sensing magnet
  if (currentState == unlockDis && digitalRead(A5) == LOW) {
    digitalWrite(A3, LOW);          // disengage the solonoid
    currentState = openDoor;
    Serial.println("Door Open");
  }


  //allow the door to be closed if hall effect sensor senses magnet
  if (currentState == openDoor && digitalRead(A5) == HIGH) {
    solonoidTimer.start(1000);           //start solonoid
    digitalWrite(A3, HIGH);              //engage solonoid     
    while (!solonoidTimer.checkExpired()) {
      //delay until solonoid locks
    }
    digitalWrite(A3, LOW);                //disengage solonoid
    
    //check if door is closed
    if (digitalRead(A5) == HIGH) {
      currentState = lockDis;
      Serial.println("Door Closed and Locked. System Disarmed.");
    }
    else {
      Serial.println("Door Still Open");
    }
  }
  
  // disengage solonoid if timer runs out and move to lock unarmed state
  if (currentState == unlockDis && solonoidTimer.checkExpired()) { //check Hall effect
    digitalWrite(A3, LOW);             //disengage solonoid to lock door
    currentState = lockDis;            //switch state
    Serial.println("Door Locked");
  }
  

  // set off alarm if photosensor stops detecting light or no keypad is entered and no magnet detected
  if (currentState == armed && (digitalRead(photoComp) == HIGH || digitalRead(A5) == LOW)) {
    currentState = alarm;               //move to alarm state
    Serial.println("Alarm going off");
  }


  // sound alarm and flash red LED while in alarm state
  while (currentState == alarm) {
    //flash red LED
    flashRedLed();
    
    //sound alarm
    soundPiezo();
  
     //check Keypad
     int keyPress = lock.checkKeyPress();
     if (code.checkCode(keyPress)) {
      unlock();
      Serial.println("Alarm turned off. System disarmed.");
     }
  }

  
}
