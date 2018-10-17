#pragma once

extern "C" {
#include <cgridvisi.h>
}
#include <dataVis.h>
#include <qtSafeViewer.h>

class GridVisiWrapper {
public:
  GridVisiWrapper(int rows, int cols, void *data, c_update_t update_func,
                  char *name);
  ~GridVisiWrapper();
  int run(int iters = -1);

private:
  QTSafeViewer *viewer;
  DataVis *visi_grid;
};
