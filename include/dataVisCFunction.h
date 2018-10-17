#pragma once

extern "C" {
#include "cgridvisi.h"
}

#include <dataVisCPU.h>

class DataVisCFunction : public DataVisCPU {

public:
  DataVisCFunction(int r, int c, void *app_data, c_update_t func);
  virtual ~DataVisCFunction();

  virtual void update();

private:
  void *app_data;
  c_update_t c_update;
};
