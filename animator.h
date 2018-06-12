#pragma once

class Animator{
public:
  Animator(){};
  virtual ~Animator(){/*do nothing*/};

  virtual void update(void* buff, int w, int h) = 0;
};
