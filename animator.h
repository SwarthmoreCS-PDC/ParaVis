#pragma once

#include "imageBuffer.h"

class Animator{
public:
  Animator(){};
  virtual ~Animator(){/*do nothing*/};

  virtual void update(ImageBuffer* img) = 0;
};
