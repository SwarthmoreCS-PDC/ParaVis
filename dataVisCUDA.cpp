#include "dataVisCUDA.h"
#include "juliaKernel.h"
#include <iostream>


DataVisCUDA::DataVisCUDA(int w, int h, int d) :
   DataVis(w,h,d),
   m_pbo(nullptr), m_animate(nullptr) {
 /* do nothing */
};

DataVisCUDA::~DataVisCUDA(){
    disconnect();
    delete m_texture; m_texture=nullptr;
}

void DataVisCUDA::init() {
  m_wrapper.init();
  createPBO();
  m_ready = true;
}

void DataVisCUDA::update(){
  if(!isReady()){ init(); }
  color3* buff = m_wrapper.map();
  m_image.buffer=buff;
  //static JuliaKernel kern(m_width,m_height,-0.8,0.156);
  if(m_animate){
    m_animate->update(&m_image);
  }
  m_wrapper.unmap();
}

void DataVisCUDA::bind(){
  m_texture->bind();
}

void DataVisCUDA::connect() {
  if(!m_pbo){
    createPBO();
  }
  m_wrapper.connect(m_pbo->bufferId());
}

void DataVisCUDA::disconnect() {
  m_wrapper.disconnect();
  destroyPBO();
}

void DataVisCUDA::textureReload() {
  update();
  m_texture->bind();
  // Read Texture data from PBO
  m_pbo->bind();
  m_texture->setData(QOpenGLTexture::RGB, QOpenGLTexture::UInt8, (const void *) nullptr);
  m_pbo->release();
}

void DataVisCUDA::createPBO(){
  destroyPBO(); // get rid of any old buffer

  // Create PBO
  int numBytes = sizeof(GLubyte) * 3 * m_width* m_height;
  m_pbo = new QOpenGLBuffer(
      QOpenGLBuffer::PixelUnpackBuffer); // Used for reading Texture data
  m_pbo->create();
  m_pbo->bind();
  m_pbo->allocate(numBytes);
  m_wrapper.connect(m_pbo->bufferId()); // Inform CUDA about PBO
  m_pbo->release();

  createTexture();
}

void DataVisCUDA::destroyPBO(){
  if (m_pbo) {
    m_pbo->release();
    delete m_pbo;
    m_pbo = nullptr;
  }
}
