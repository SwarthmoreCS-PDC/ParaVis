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
}
