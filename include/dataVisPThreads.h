
#pragma once

#include "dataVisCPU.h"
#include <pthread.h>

#ifdef __APPLE__
#include <osx/pthread_barrier.h>
#endif

class DataVisPThreads : public DataVisCPU {

public:
  DataVisPThreads(int num_tids, int r, int c);
  virtual ~DataVisPThreads();

  void update();

private:
  int m_numThreads;
  pthread_barrier_t m_barrier;
};
