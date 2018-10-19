#include "cvisi_struct.h"
#include "dataVisCFunction.h"
#include "gridVisiWrapper.h"

extern "C" {
#include <cgridvisi.h>

void init_and_run_animation(int rows, int cols, void *data,
                            c_update_t update_func, char *name, int iters) {
  GridVisiWrapper wrapper(name);
  DataVis *anim = new DataVisCFunction(rows, cols, data, update_func);
  wrapper.setAnimation(anim);
  wrapper.run(iters);
}

/*
 *  get the color3 buffer associated with a visualization
 *   handle:  a handle to a visualization
 *   returns: pointer to color3 buffer for the visi, or NULL on error
 */
color3 *get_animation_buffer(visi_handle handle) {
  handle->app->setAnimation(handle->visi_grid);
  return handle->app->getBuffer();
}

/*
 * notify the visi library that a thread's update to a buffer is ready
 * (called by each thread after it updates its portion of the buffer
 * to reflect the next computation step)
 */
void draw_ready(visi_handle handle) {

  // wait on the visi barrier
  handle->app->setAnimation(handle->visi_grid);
  handle->app->update();
}

/*
 * runs the pthread animation: called by all threads in their main loop
 *   handle:  value returned by call to init_pthread_animation
 *   iters: run for specified number of iterations, or if 0 run forever
 */
void run_animation(visi_handle handle, int iters) {

  if (!handle) {
    printf("Error: passing NULL handle to run_pthread_animation\n");
    return;
  }
  handle->app->setAnimation(handle->visi_grid);
  handle->app->run(iters);
}
}
