#pragma once

#include <QOpenGLBuffer>
#include <QOpenGLTexture>
//#include "qoglHelper.h"
#include "cudaWrapper.h"
#include "animator.h"
#include "imageBuffer.h"

class DataVisCUDA {

public:
  // Depth d currently not used
  DataVisCUDA(int w, int h, int d=1);
  virtual ~DataVisCUDA();

  virtual void update();

  void bind();
  void textureReload();

  inline void setAnimator( Animator* animate){
    m_animate = animate;
  }

protected:
  int m_width, m_height, m_depth;
  bool m_ready;
  QOpenGLTexture *m_texture;
  ImageBuffer m_image;

private:
  QOpenGLBuffer *m_pbo; /* Pixel Buffer Object */
  CUDAWrapper m_wrapper;
  Animator* m_animate;
  void createPBO();
  void destroyPBO();
  inline bool isReady(){ return m_ready; }


  /* Call CUDA initializization during OpenGL init */
  void init();

  /* Connect Pixel Buffer Object with buffID to
   * CUDA resource */
  void connect();

  /* Release CUDA resource connected to Pixel Buffer*/
  void disconnect();

};
