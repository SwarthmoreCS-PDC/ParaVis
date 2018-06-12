#pragma once

#include <QOpenGLBuffer>
#include "qoglHelper.h"
#include "cudaWrapper.h"
#include "animator.h"

class DataVisCUDA : protected QOGLHelper {

public:
  DataVisCUDA(int w, int h);
  virtual ~DataVisCUDA(){};

  virtual void update();

  /* Call CUDA initializization during OpenGL init */
  void init();

  /* Connect Pixel Buffer Object with buffID to
   * CUDA resource */
  void connect();

  /* Release CUDA resource connected to Pixel Buffer*/
  void disconnect();

  void textureReload();

  inline bool isReady(){ return m_ready; }

  inline void setAnimator( Animator* animate){
    m_animate = animate;
  }

private:
  int m_width, m_height;
  bool m_ready;
  QOpenGLBuffer *m_pbo; /* Pixel Buffer Object */
  CUDAWrapper m_wrapper;
  Animator* m_animate;
  void createPBO();
  void destroyPBO();



};
