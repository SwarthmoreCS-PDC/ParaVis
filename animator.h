#pragma once

#include "color3.h"

class Animator{
public:
  Animator(){};
  virtual ~Animator(){/*do nothing*/};

  virtual void update(color3* buff, int w, int h) = 0;
};
