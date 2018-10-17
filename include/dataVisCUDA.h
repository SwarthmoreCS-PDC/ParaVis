#pragma once

#include "animator.h"
#include "cudaWrapper.h"
#include "dataVis.h"
#include <QOpenGLBuffer>

/* TODO: clean up the implementation of this perhaps?
   unclear if the map/unmap is needed on every update
   maybe some helper methods can be simplified
*/

/* DataVisCUDA provides a CUDA specific implementation of
   most of the DataVis interface. The primary role of this
   class is to allocate the Image Buffer memory on the GPU
   and connect this memory to both CUDA and OpenGL.
   This class provides an implementaion of textureReload
   and an implementation of update.

   However, since the CUDA compiler nvcc cannot compile
   this header file without warnings, it is not recommended
   to directly inherit from this class to implement
   a user specific animation. Instead, for CUDA-specific
   implementations, users should instead inherit and implement
   the simpler Animator class and use the setAnimator() method
   in this class class to connect their Animator to the
   DataVisCUDA class
*/
class DataVisCUDA : public DataVis {

public:
  // Depth d currently not used
  DataVisCUDA(int w, int h, int d = 1);
  virtual ~DataVisCUDA();

  virtual void update();

  void textureReload();

  inline void setAnimator(Animator *animate) { m_animate = animate; }

private:
  QOpenGLBuffer *m_pbo;  /* Pixel Buffer Object */
  CUDAWrapper m_wrapper; /* Hides CUDA code from Qt */
  Animator *m_animate;   /* User provided animation routine */

  /* Allocate GPU Pixel Buffer Object for Image Buffer memory */
  void createPBO();

  /* Clean up PBO on GPU */
  void destroyPBO();

  /* Delayed constructon of CUDA buffers once OpenGL/CUDA context
     is available */
  void init();

  /* Connect Pixel Buffer Object to CUDA resource */
  void connect();

  /* Release CUDA resource connected to Pixel Buffer*/
  void disconnect();
};
