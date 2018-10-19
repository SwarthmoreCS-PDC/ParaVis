
#include "gridVisiWrapper.h"

GridVisiWrapper::GridVisiWrapper(char *name)
    : m_viewer(nullptr), m_visi_grid(nullptr) {
  m_viewer = new QTSafeViewer(600, 500, name);
}

GridVisiWrapper::~GridVisiWrapper() {
  delete m_viewer;
  m_viewer = nullptr;
  /* Viewer semantics is that it will destroy m_visi_grid for us */
  m_visi_grid = nullptr;
}

void GridVisiWrapper::setAnimation(DataVis *anim) {
  m_visi_grid = anim;
  m_viewer->setAnimation(m_visi_grid);
}

int GridVisiWrapper::run(int iters) {
  if (iters > 0) {
    return m_viewer->run(iters);
  } else {
    return m_viewer->run();
  }
}
