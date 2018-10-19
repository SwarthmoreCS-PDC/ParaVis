
#pragma once

#include "dataVisCPU.h"
#include "qtSafeViewer.h"
#include <pthread.h>

#ifdef __APPLE__
#include <osx/pthread_barrier.h>
#endif

extern "C" {
#include "pthreadGridVisi.h"
}

class PthreadGridVisiWrapper : public DataVisCPU {

public:
  PthreadGridVisiWrapper(int num_tids, int r, int c);
  virtual ~PthreadGridVisiWrapper();

  void update();

private:
  int m_numThreads;
  pthread_barrier_t m_barrier;
};
