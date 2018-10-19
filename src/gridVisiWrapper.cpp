
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

void GridVisiWrapper::setAnimation(DataVis *anim) { m_visi_grid = anim; }

void GridVisiWrapper::update() { m_visi_grid->update(); }

color3 *GridVisiWrapper::getBuffer() {
  if (!m_visi_grid) {
    return nullptr;
  }
  return m_visi_grid->getImageData().buffer;
}

int GridVisiWrapper::run(int iters) {
  m_viewer->setAnimation(m_visi_grid);
  if (iters > 0) {
    return m_viewer->run(iters);
  } else {
    return m_viewer->run();
  }
}
