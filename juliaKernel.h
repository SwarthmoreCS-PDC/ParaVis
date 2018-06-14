#pragma once

#include "animator.h"
#include "color3.h"
#include <cuda.h>

/* Julia Kernel stuff */
class JuliaKernel: public Animator {

public:
  JuliaKernel(float re, float im):
    m_re(re), m_im(im), m_ticks(0){ };
  ~JuliaKernel(){};

  void update(color3* buff, int w, int h);

private:
  float m_re, m_im;
  int m_ticks;
  
};
