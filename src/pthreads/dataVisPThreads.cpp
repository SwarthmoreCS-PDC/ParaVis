#include "dataVisPThreads.h"

DataVisPThreads::DataVisPThreads(int ntids, int r, int c)
    : DataVisCPU(c, r), m_numThreads(ntids) {
  /*  init barrier to ntids+1: ntids application threads + the
      thread running opengl event loop and calling the update function
      (probably in the context of the main program thread)
  */
  if (pthread_barrier_init(&m_barrier, NULL, (m_numThreads + 1))) {
    perror("pthread_barrier_init failed\n");
  }
}

DataVisPThreads::~DataVisPThreads() {
  pthread_barrier_wait(&m_barrier);
  pthread_barrier_destroy(&m_barrier);
}

void DataVisPThreads::update() { pthread_barrier_wait(&m_barrier); }
