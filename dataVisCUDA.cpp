#include "dataVisCUDA.h"
#include "juliaKernel.h"

DataVisCUDA::DataVisCUDA(int w, int h) :
   m_width(w), m_height(h), m_pbo(NULL) { };

void DataVisCUDA::init() { m_wrapper.init(); }

void DataVisCUDA::connect() {
  if(!m_pbo){
    createPBO();
  }
  m_wrapper.connect(m_pbo->bufferId());
}

void DataVisCUDA::disconnect() {
  m_wrapper.disconnect();
}

void DataVisCUDA::update(){
  JuliaKernel kern(m_width,m_height);
  kern.run(m_wrapper.map(), -0.8, 0.156);
}

void DataVisCUDA::createPBO(){
  destroyPBO(); // get rid of any old buffer

  // Create PBO
  int numBytes = sizeof(GLubyte) * 4 * m_width* m_height;
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
