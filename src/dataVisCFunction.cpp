#include "dataVisCFunction.h"

DataVisCFunction::DataVisCFunction(int r, int c, void *data, c_update_t func)
    : DataVisCPU(c, r), app_data(data), c_update(func){};

DataVisCFunction::~DataVisCFunction() { /* do nothing */
}

void DataVisCFunction::update() { c_update(m_image.buffer, app_data); }
