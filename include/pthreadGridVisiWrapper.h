
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
  color3 *get_buff();

private:
  int ntids;
  pthread_barrier_t visi_barrier;
};
