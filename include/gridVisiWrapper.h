#pragma once

extern "C"{
  #include "cgridvisi.h"
}
#include <qtViewer.h>
#include <dataVis.h>

class GridVisiWrapper{
public:
   GridVisiWrapper(int rows, int cols,
        void* data, c_update_t update_func,
        char *name);
   ~GridVisiWrapper();
   int run(int iters=-1);

private:
  QTViewer *viewer;
  DataVis  *visi_grid;
  int argc;
  char* argv[1];
};