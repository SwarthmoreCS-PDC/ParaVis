#pragma once


#include "dataVisCPU.h"

/* Eventually a PThreads Demo */
class PThreadVis: public DataVisCPU {

public:
  // Depth d currently not used
  PThreadVis(int w, int h, int d=1);
  virtual ~PThreadVis();

  void update();

private:
  int m_ticks;
  
};
