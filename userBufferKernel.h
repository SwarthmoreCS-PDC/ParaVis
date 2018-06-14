#pragma once

#include "animator.h"
#include <cuda.h>

/* UserBuffer Kernel stuff */
class UserBufferKernel: public Animator {

public:
  UserBufferKernel(int w, int h);
  ~UserBufferKernel();

  void update(ImageBuffer* img);

private:
  int* m_dev_grid;
  int m_rows, m_cols;
};
