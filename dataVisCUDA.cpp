#include "dataVisCUDA.h"
#include "juliaKernel.h"
#include <iostream>


DataVisCUDA::DataVisCUDA(int w, int h, int d) :
   m_width(w), m_height(h), m_depth(d),
   m_ready(false), m_pbo(nullptr),
   m_animate(nullptr) {

     m_image.height=h;
     m_image.width=w;
     m_image.depth=d;
     m_image.buffer=nullptr;
};

void DataVisCUDA::init() {
  m_wrapper.init();
  createPBO();
  m_ready = true;
}

void DataVisCUDA::update(){
  color3* buff = m_wrapper.map();
  m_image.buffer=buff;
  //static JuliaKernel kern(m_width,m_height,-0.8,0.156);
  if(m_animate){
    m_animate->update(&m_image);
  }
  m_wrapper.unmap();
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
  // Read Texture data from PBO
  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_pbo->bufferId());
  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, GL_RGB,
                  GL_UNSIGNED_BYTE, NULL);
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
}

void DataVisCUDA::destroyPBO(){
  if (m_pbo) {
    m_pbo->release();
    delete m_pbo;
    m_pbo = NULL;
  }
}
