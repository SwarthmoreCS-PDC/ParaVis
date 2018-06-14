#pragma once

#include "color3.h"

typedef struct{
  color3* buffer;
  int height;
  int width;
  int depth;  //Currently not used
} ImageBuffer;
