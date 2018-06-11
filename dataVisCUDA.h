#pragma once

#include <QOpenGLBuffer>
#include <QOpenGLFunctions_4_1_Core>
#include "cudaWrapper.h"

class DataVisCUDA : protected QOpenGLFunctions_4_1_Core {

public:
  DataVisCUDA(int w, int h);
  virtual ~DataVisCUDA(){};

  virtual void update(float re, float im);

  /* Call CUDA initializization during OpenGL init */
  void init();

  /* Connect Pixel Buffer Object with buffID to
   * CUDA resource */
  void connect();

  /* Release CUDA resource connected to Pixel Buffer*/
  void disconnect();

  void textureReload();

private:
  int m_width, m_height;
  QOpenGLBuffer *m_pbo; /* Pixel Buffer Object */
  CUDAWrapper m_wrapper;

  void createPBO();
  void destroyPBO();



};
