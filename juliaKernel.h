#pragma once

#include <cuda.h>

/* Julia Kernel stuff */
class JuliaKernel {

public:
  JuliaKernel(int w, int h):m_width(w), m_height(h){};
  ~JuliaKernel(){};

  void run(void* buff, float re, float im);

private:
  int m_width, m_height;
};
