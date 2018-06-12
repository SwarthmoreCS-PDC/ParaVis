#pragma once

#include <QOpenGLBuffer>
#include "qoglHelper.h"
#include "cudaWrapper.h"

class DataVisCUDA : protected QOGLHelper {

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

  inline bool isReady(){ return m_ready; }

private:
  int m_width, m_height;
  bool m_ready;
  QOpenGLBuffer *m_pbo; /* Pixel Buffer Object */
  CUDAWrapper m_wrapper;

  void createPBO();
  void destroyPBO();



};
