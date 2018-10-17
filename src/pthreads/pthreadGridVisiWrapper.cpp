#include "pthreadGridVisiWrapper.h"
#include "qtSafeViewer.h"
#include <dataVis.h>
#include <stdio.h> // for perror

struct visi_pthread_struct {
  QTSafeViewer *viewer;
  PthreadGridVisiWrapper *visi_grid;
};

/* initialize the visualization: only call once (by one thread)
 *
 *     num_tids: total number of threads participating in the computation
 *     rows: number of rows
 *     cols: number of cols
 *     name: name for visi window
 *     iters: run for specified number of iterations, or if 0 run forever
 *     returns: a pthread_visi_handle or NULL on error
 */
extern "C" visi_pthread_handle init_pthread_animation(int num_tids, int rows,
                                                      int cols, char *name,
                                                      int iters) {

  visi_pthread_handle handle; // pointer to pthread_visi_struct

  handle = (visi_pthread_handle)malloc(sizeof(struct visi_pthread_struct));
  if (!handle) {
    printf("Error: malloc failed\n");
    return NULL;
  }
  handle->viewer = new QTSafeViewer(600, 500, name);
  handle->visi_grid = new PthreadGridVisiWrapper(num_tids, rows, cols);
  return handle;
}

/*
 *  get the color3 buffer associated with a visualization
 *   handle:  a handle to a visualization
 *   returns: pointer to color3 buffer for the visi, or NULL on error
 */
extern "C" color3 *get_buff_pthread_animation(visi_pthread_handle handle) {

  return handle->visi_grid->get_buff();
}

/*
 * notify the visi library that a thread's update to a buffer is ready
 * (called by each thread after it updates its portion of the buffer
 * to reflect the next computation step)
 */
extern void draw_pthread_animation(visi_pthread_handle handle) {

  // wait on the visi barrier
  handle->visi_grid->update();
}

/*
 * runs the pthread animation: called by all threads in their main loop
 *   visi_info:  value returned by call to init_pthread_animation
 *   iters: run for specified number of iterations, or if 0 run forever
 */
extern "C" void run_pthread_animation(visi_pthread_handle visi_info,
                                      int iters) {

  if (!visi_info) {
    printf("Error: passing NULL visi_info to run_pthread_animation\n");
    return;
  }
  visi_info->viewer->setAnimation(visi_info->visi_grid);
  if (iters) {
    visi_info->viewer->run(iters);
  } else {
    visi_info->viewer->run();
  }
}

PthreadGridVisiWrapper::PthreadGridVisiWrapper(int t, int r, int c)
    : DataVisCPU(c, r), ntids(t) {
  // init barrier to ntids+1: ntids application threads + the
  // thread running opengl event loop and calling the update function
  // (probably in the context of the main program thread)
  if (pthread_barrier_init(&(this->visi_barrier), NULL, (ntids + 1))) {
    perror("pthread_barrier_init failed\n");
  }
}

PthreadGridVisiWrapper::~PthreadGridVisiWrapper() { /* do nothing ? */
}

color3 *PthreadGridVisiWrapper::get_buff() { return this->m_image.buffer; }

void PthreadGridVisiWrapper::update() {

  // c_update(m_image.buffer, app_data);
  pthread_barrier_wait(&visi_barrier);
}
