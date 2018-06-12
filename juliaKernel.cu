#include <cuda.h>
#include <iostream>
#include "juliaKernel.h"

__device__ int julia(int x, int y, int w, int h, float re, float im);
__global__ void kernel(uchar3 *ptr, int w, int h, float re, float im);


void JuliaKernel::run(void* buff, float re, float im) {

  dim3 grid(m_width, m_height);
  im += 0.2 * sin(m_ticks/20.);
  re += 0.3 * cos(m_ticks/17.);
  kernel<<<grid, 1>>>((uchar3*)buff, m_width, m_height, re, im);
  m_ticks = (m_ticks+1)%1234;
}

struct cuComplex {
  float r;
  float i;
  __device__ cuComplex(float a, float b) : r(a), i(b) {}
  __device__ float magnitude2(void) { return r * r + i * i; }
  __device__ cuComplex operator*(const cuComplex &a) {
    return cuComplex(r * a.r - i * a.i, i * a.r + r * a.i);
  }
  __device__ cuComplex operator+(const cuComplex &a) {
    return cuComplex(r + a.r, i + a.i);
  }
};

__device__ int julia(int x, int y, int w, int h, float re, float im) {
  const float scale = 1.5;
  float jx = scale * (float)(w / 2 - x) / (h / 2);
  float jy = scale * (float)(h / 2 - y) / (h / 2);

  cuComplex c(re, im);
  cuComplex a(jx, jy);

  int i = 0;
  for (i = 0; i < 200; i++) {
    a = a * a + c;
    if (a.magnitude2() > 1000) {
      return 0;
    }
  }

  return 1;
}

__global__ void kernel(uchar3 *ptr, int w, int h, float re, float im) {
  // map from threadIdx/BlockIdx to pixel position
  int x = blockIdx.x;
  int y = blockIdx.y;
  int offset = x + y * gridDim.x;

  // now calculate the value at that position
  int juliaValue = julia(x, y, w, h, re, im);
  ptr[offset].x = 255 * juliaValue;
  ptr[offset].y = 0;
  ptr[offset].z = 64 * (1 - juliaValue);
}
