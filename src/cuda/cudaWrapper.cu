#include "cudaWrapper.h"
#include <cstdio>
#include <cuda.h>
#include <cuda_gl_interop.h>

CUDAWrapper::CUDAWrapper() : m_pbo_CUDA(nullptr){};

void CUDAWrapper::init() {
  /* deprecated as of CUDA 5.0 */
  // cudaGLSetGLDevice(0);
}

void CUDAWrapper::connect(GLuint buffID) {
  if (m_pbo_CUDA) {
    disconnect();
  }
  cudaGraphicsGLRegisterBuffer(&m_pbo_CUDA, buffID,
                               cudaGraphicsRegisterFlagsNone);
}

void CUDAWrapper::disconnect() {
  if (m_pbo_CUDA) {
    cudaGraphicsUnregisterResource(m_pbo_CUDA);
    m_pbo_CUDA = nullptr;
  }
}

bool CUDAWrapper::copyToGPU(color3 *cpuBuff, int width, int height) {
  color3 *dev_img = this->map();
  cudaError_t err;
  err = cudaMemcpy(dev_img, cpuBuff, sizeof(color3) * width * height,
                   cudaMemcpyHostToDevice);
  return (err == cudaSuccess);
}

color3 *CUDAWrapper::map() {

  color3 *dev_pixBuffer;
  size_t numBytes;

  // Map buffer object for writing from CUDA
  cudaGraphicsMapResources(1, &m_pbo_CUDA);
  cudaGraphicsResourceGetMappedPointer((void **)&dev_pixBuffer, &numBytes,
                                       m_pbo_CUDA);
  return dev_pixBuffer;
}

void CUDAWrapper::unmap() {
  cudaThreadSynchronize(); // Make sure kernel is done
  // Return PBO to OpenGL control.
  cudaGraphicsUnmapResources(1, &m_pbo_CUDA);
}
