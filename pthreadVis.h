#pragma once


#include "dataVisCPU.h"

typedef struct {
  int nThreads;
  int id;
  int ticks;
  ImageBuffer* img;
} threadInfo;

/* Eventually a PThreads Demo */
class PThreadVis: public DataVisCPU {

public:
  // Depth d currently not used
  PThreadVis(int numThreads, int w, int h, int d=1);
  virtual ~PThreadVis();

  void update();

private:
  int m_ticks;
  int m_numThreads;

};
