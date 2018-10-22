#include "cvisi_struct.h"
#include "dataVisCFunction.h"
#include "gridVisiWrapper.h"
#include <iostream>

extern "C" {
#include <cgridvisi.h>

void init_and_run_animation(int rows, int cols, void *data,
                            c_update_t update_func, char *name, int iters) {
  GridVisiWrapper wrapper(name);
  DataVis *anim = new DataVisCFunction(rows, cols, data, update_func);
  wrapper.setAnimation(anim);
  wrapper.run(iters);
}

visi_handle init_c_animation(int rows, int cols,
                                              char *name, int iters) {

  visi_handle handle = nullptr;
  DataVis *anim = nullptr;
  GridVisiWrapper *app = nullptr;

  try {
    handle = new visi_struct;
    app = new GridVisiWrapper(name);
    /*TODO: create new class similar to DataVisPThreads */
  } catch (std::bad_alloc &ba) {
    std::cerr << "bad_alloc caught: " << ba.what() << '\n';
    return nullptr;
  }
  handle->app = app;
  handle->app->setAnimation(anim);
  return handle;
}

color3 *get_animation_buffer(visi_handle handle) {
  return handle->app->getBuffer();
}

void draw_ready(visi_handle handle) { handle->app->update(); }

void run_animation(visi_handle handle, int iters) {

  if (!handle) {
    printf("Error: passing NULL handle to run_pthread_animation\n");
    return;
  }
  handle->app->run(iters);
}

} // Extern C
