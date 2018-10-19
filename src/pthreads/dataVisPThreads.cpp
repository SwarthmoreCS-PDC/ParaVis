#include "dataVisPThreads.h"
#include "cvisi_struct.h"
#include "gridVisiWrapper.h"
#include <cstdio>   //for perror
#include <iostream> // for cerr
#include <new>      //for bad_alloc

/* initialize the visualization: only call once (by one thread)
 *
 *     num_tids: total number of threads participating in the computation
 *     rows: number of rows
 *     cols: number of cols
 *     name: name for visi window
 *     iters: run for specified number of iterations, or if 0 run forever
 *     returns: a pthread_visi_handle or NULL on error
 */
extern "C" visi_handle init_pthread_animation(int num_tids, int rows, int cols,
                                              char *name, int iters) {

  visi_handle handle = nullptr; // pointer to pthread_visi_struct
  DataVisPThreads *anim = nullptr;
  GridVisiWrapper *app = nullptr;

  try {
    handle = new visi_struct;
    app = new GridVisiWrapper(name);
    anim = new DataVisPThreads(num_tids, rows, cols);
  } catch (std::bad_alloc &ba) {
    std::cerr << "bad_alloc caught: " << ba.what() << '\n';
    return nullptr;
  }
  handle->app = app;
  handle->app->setAnimation(anim);
  return handle;
}

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
