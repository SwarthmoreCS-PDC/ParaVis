#pragma once

#include <QtOpenGL>
#include "cudaWrapper.h"

class DataVisCUDA {

public:
  DataVisCUDA(int w, int h);
  ~DataVisCUDA(){};

  virtual void update();

private:
  int m_width, m_height;
  QOpenGLBuffer *m_pbo; /* Pixel Buffer Object */
  CUDAWrapper m_wrapper;

  void createPBO();
  void destroyPBO();
    /* Call CUDA initializization during OpenGL init */
  void init();

  /* Connect Pixel Buffer Object with buffID to
   * CUDA resource */
  void connect();

  /* Release CUDA resource connected to Pixel Buffer*/
  void disconnect();


};
