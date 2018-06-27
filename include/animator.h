#pragma once

#include "imageBuffer.h"

/* A small interface class for implementing CUDA
   animatations. Users should create a class that
   inherits from Animator and implement the update(...)
   method using CUDA to populate the color image buffer.

   Once implemented, the user can connect the Animator
   to an instance of the DataVisCUDA class using the
   set Animator class and then provide the DataVisCUDA
   pointer to a qtViewer object for animating
*/
class Animator{
public:
  Animator(){};
  virtual ~Animator(){/*do nothing*/};

  /* A pure virtual function that users must
     implement in a derived class. The
     ImageBuffer argument will already have a
     GPU allocated buffer set by the DataVisCUDA
     class
  */
  virtual void update(ImageBuffer* img) = 0;
};
