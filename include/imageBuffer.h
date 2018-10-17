#pragma once

#include "color3.h"

/* A small struct for storing all the info about
   the color image buffer */
typedef struct {
  /* array of pixels in row major order, with top row=0 listed first */
  color3 *buffer;
  /* height of image buffer in number of rows */
  int height;
  /* width of image buffer in number of columns */
  int width;
  /* depth of image buffer in number of slices */
  int depth; // Currently not used
} ImageBuffer;

/*TODO: add namespace? */
