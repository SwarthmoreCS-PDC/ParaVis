#pragma once

#include <dataVis.h>
#include <qtSafeViewer.h>

/* A small wrapper class that allows C programs to connect
   to C++ interface */
class GridVisiWrapper {
public:
  GridVisiWrapper(char *name);
  ~GridVisiWrapper();
  int run(int iters = -1);
  void setAnimation(DataVis *anim);
  void update();
  color3 *getBuffer();

private:
  QTSafeViewer *m_viewer;
  DataVis *m_visi_grid;
};
