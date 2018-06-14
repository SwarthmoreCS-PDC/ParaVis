#pragma once

#include <GL/gl.h>
#include <cuda.h>
#include "color3.h"

/* Wrapper class for connecting OpenGL context to CUDA */
class CUDAWrapper {

public:
  CUDAWrapper();
  ~CUDAWrapper(){};

  /* Call CUDA initializization during OpenGL init */
  void init();

  /* Connect Pixel Buffer Object with buffID to
   * CUDA resource */
  void connect(GLuint buffID);

  /* Release CUDA resource connected to Pixel Buffer*/
  void disconnect();

  color3* map();

  void unmap();

private:
  struct cudaGraphicsResource *m_pbo_CUDA;
};
