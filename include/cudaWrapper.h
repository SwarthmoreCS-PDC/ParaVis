#pragma once

#include "color3.h"
#ifdef _WIN32
#include<windows.h>
#endif
#include <GL/gl.h>
#include <cuda.h>

/* TODO: Check if this can be simplified
  https://docs.nvidia.com/cuda/cuda-runtime-api/group__CUDART__INTEROP.html#group__CUDART__INTEROP
  */

/* A class compiled by NVCC that shares GPU memory buffers
   to OpenGL and CUDA contexts */
class CUDAWrapper {

public:
  CUDAWrapper();
  ~CUDAWrapper(){};

  /* Call CUDA initialization during OpenGL init */
  void init();

  /* Connect Pixel Buffer Object with buffID to
   * CUDA resource */
  void connect(GLuint buffID);

  /* Release CUDA resource connected to Pixel Buffer*/
  void disconnect();

  /* copy color buffer on CPU to color buffer on GPU.
     Assumes GPU buffer is already allocated and available
     through map(). Returns true if copy was successful,
     false if error */
  bool copyToGPU(color3 *cpuBuff, int width, int height);

  /* Get a GPU pointer to mapped GPU memory */
  color3 *map();

  /* Release GPU memory from being used in a CUDA context */
  void unmap();

private:
  struct cudaGraphicsResource *m_pbo_CUDA;
};
