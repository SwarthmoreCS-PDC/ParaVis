#include "dataVisCPU.h"


DataVisCPU::DataVisCPU(int w, int h, int d) :
   DataVis(w,h,d) {
     m_image.buffer = new color3[w*h];
     createTexture();
     m_ready = true;
};

DataVisCPU::~DataVisCPU(){
    delete m_image.buffer; m_image.buffer=nullptr;
}

void DataVisCPU::textureReload() {
  update();
  m_texture->bind();
  m_texture->setData(QOpenGLTexture::RGB, QOpenGLTexture::UInt8, (const void *) m_image.buffer, &m_options);
}
