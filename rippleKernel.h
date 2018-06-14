#pragma once

#include "animator.h"
#include "color3.h"
#include <cuda.h>

/* Ripple Kernel stuff */
class RippleKernel: public Animator {

public:
  RippleKernel(): m_ticks(0){ };
  ~RippleKernel(){};

  void update(color3* buff, int w, int h);

private:
  int m_ticks;
  
};
