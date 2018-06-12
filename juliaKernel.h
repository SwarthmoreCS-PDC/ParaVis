#pragma once

#include "animator.h"
#include <cuda.h>

/* Julia Kernel stuff */
class JuliaKernel: public Animator {

public:
  JuliaKernel(float re, float im):
    m_re(re), m_im(im), m_ticks(0){ };
  ~JuliaKernel(){};

  void update(void* buff, int w, int h);

  void run(void* buff, float re, float im);

private:
  float m_re, m_im;
  int m_ticks;
};
