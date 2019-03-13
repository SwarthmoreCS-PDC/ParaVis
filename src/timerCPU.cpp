/* Copyright 2016-2018
 * Swarthmore College Computer Science, Swarthmore PA
 * T. Newhall, A. Danner
 */
#include "timerCPU.h"

CPUTimer::CPUTimer() {
  /* Do nothing */
}

void CPUTimer::start() { startTime = QDateTime::currentDateTime(); }

void CPUTimer::stop() {
  stopTime = QDateTime::currentDateTime();
}

void CPUTimer::print() {
  float diff = startTime.msecsTo(stopTime);
  printf("Elapsed time: %.3f \n", diff);
}

float CPUTimer::elapsed() {
  QDateTime now = QDateTime::currentDateTime();
  return startTime.msecsTo(now);
}
