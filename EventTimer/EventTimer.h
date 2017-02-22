// EventTimer Class

#ifndef EVENTTIMER_H
#define EVENTTIMER_H

#include "arduino.h"

class EventTimer
{
  protected:
  bool isRunning;
  long startTime;
  long duration;

  public:
  // constructor
  EventTimer();
  
  // start timer for input duration (in ms)
  void start(long d);

  // turn off timer
  void cancel();

  // return true if timer is running and time is past end time
  bool checkExpired();

  // return isRunning
  bool getIsRunning();
};

#endif