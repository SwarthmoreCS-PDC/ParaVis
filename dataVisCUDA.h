#pragma once

#include <QOpenGLBuffer>
#include "qoglHelper.h"
#include "cudaWrapper.h"
#include "animator.h"
#include "imageBuffer.h"

class DataVisCUDA : protected QOGLHelper {

public:
  // Depth d currently not used
  DataVisCUDA(int w, int h, int d=1);
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
  int m_width, m_height, m_depth;
  bool m_ready;
  QOpenGLBuffer *m_pbo; /* Pixel Buffer Object */
  CUDAWrapper m_wrapper;
  Animator* m_animate;
  ImageBuffer m_image;
  void createPBO();
  void destroyPBO();



};
