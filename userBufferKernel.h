#pragma once

#include "animator.h"
#include "color3.h"
#include <cuda.h>

/* UserBuffer Kernel stuff */
class UserBufferKernel: public Animator {

public:
  UserBufferKernel(int w, int h);
  ~UserBufferKernel();

  void update(color3* buff, int w, int h);

private:
  int* m_dev_grid;
  int m_rows, m_cols;
};
