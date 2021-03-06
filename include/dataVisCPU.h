#pragma once

#include "dataVis.h"

/* DataVisCPU provides an implementation of
   most of the DataVis interface where the image buffer is
   allocated in CPU memory.
   This class provides an implementaion of textureReload
   but leaves the implementation of update to the user.
*/
class DataVisCPU : public DataVis {

public:
  // Depth d currently not used
  DataVisCPU(int w, int h, int d = 1);

  /* Construct a new visualization using the provided image file
     name for the initial dimensions and colors */
  DataVisCPU(QString imgFileName);

  virtual ~DataVisCPU();

  void textureReload();
};
