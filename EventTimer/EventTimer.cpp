// Timer Implementaion

#include "EventTimer.h"

// constructor
EventTimer::EventTimer(){
    isRunning = false;
    startTime = 0;
    duration = 0;
}


// start timer for input duration (in ms)
void EventTimer::start(long d){
    duration = d;
    isRunning = true;
    startTime = millis();
}

// turn off timer
void EventTimer::cancel(){
	isRunning = false;
}

// return true if timer is running and time is past end time
bool EventTimer::checkExpired() {
    if ((millis() - startTime >= duration) && isRunning)
    {
      isRunning = false;
      return true;
    }
    return false;
}

// return isRunning
bool EventTimer::getIsRunning() {
    return isRunning;
}