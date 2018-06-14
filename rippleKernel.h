#pragma once

#include "animator.h"
#include <cuda.h>

/* Ripple Kernel stuff */
class RippleKernel: public Animator {

public:
  RippleKernel(): m_ticks(0){ };
  ~RippleKernel(){};

  void update(ImageBuffer* img);

private:
  int m_ticks;

};
