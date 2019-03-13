/* Copyright 2016-2018
 * Swarthmore College Computer Science, Swarthmore PA
 * T. Newhall, A. Danner
 */
#pragma once

#include "timerBase.h"
#include <QDateTime>

/* Time events on CPU side
   See timerBase for method description
 */
class CPUTimer : public TimerBase {
private:
  // store start/stop times
  QDateTime startTime, stopTime;

public:
  CPUTimer();   // Create a timer
  ~CPUTimer() { /*do nothing*/
  }
  void start();
  void stop();
  void print();
  float elapsed();
};
