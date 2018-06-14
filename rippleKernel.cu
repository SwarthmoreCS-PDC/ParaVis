#include <cuda.h>
#include <iostream>
#include "rippleKernel.h"

__global__ void kernel(color3 *ptr, int w, int h, int ticks);

void RippleKernel::update(ImageBuffer* img) {
  int tdim = 8;
  int w = img->width;
  int h = img->height;
  dim3 blocks((w+(tdim-1)) / tdim, (h+(tdim-1)) / tdim);
  dim3 threads_block(tdim, tdim);
  kernel<<<blocks, threads_block>>>(img->buffer, w, h, m_ticks);
  m_ticks += 2;
}

__global__ void kernel(color3 *ptr, int w, int h, int ticks) {
// map from threadIdx/BlockIdx to pixel position
  int x = threadIdx.x + blockIdx.x * blockDim.x;
  int y = threadIdx.y + blockIdx.y * blockDim.y;
  int offset = x + y * w;

  // compute distance from center of image
  float fx = x - w / 2;
  float fy = y - h / 2;
  float d = sqrtf(fx * fx + fy * fy);
  unsigned char grey = (unsigned char)(128.0f +
                                       127.0f * cos(d / 10.0f - ticks / 7.0f) /
                                           (d / 10.0f + 1.0f));
  ptr[offset].r = grey;
  ptr[offset].g = grey;
  ptr[offset].b = grey;
}
