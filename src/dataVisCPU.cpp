#include "dataVisCPU.h"

DataVisCPU::DataVisCPU(int w, int h, int d) : DataVis(w, h, d) {
  m_image.buffer = new color3[w * h];
  createTexture();
  m_ready = true;
};

DataVisCPU::DataVisCPU(QString imgFileName): DataVis(imgFileName) {
  if (m_width*m_height > 0){
    m_image.buffer = new color3[m_width * m_height];
    createTexture();
  }

  /*load pixels from image in filename directly into color3 buffer */
  loadPixels(m_image.buffer);

  m_ready = true;
}

DataVisCPU::~DataVisCPU() {
  delete m_image.buffer;
  m_image.buffer = nullptr;
}

void DataVisCPU::textureReload() {
  update();
  m_texture->bind();
  m_texture->setData(QOpenGLTexture::RGB, QOpenGLTexture::UInt8,
                     (const void *)m_image.buffer, &m_options);
}
