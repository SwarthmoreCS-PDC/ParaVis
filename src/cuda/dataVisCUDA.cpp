#include "dataVisCUDA.h"
#include <cstdio>

DataVisCUDA::DataVisCUDA(int w, int h, int d)
    : DataVis(w, h, d), m_pbo(nullptr), m_animate(nullptr) {
  /* do nothing */
}

DataVisCUDA::DataVisCUDA(QString imgFileName)
    : DataVis(imgFileName), m_pbo(nullptr), m_animate(nullptr) {
  /* do nothing here. Defer copying image pixel until init()
    when CUDA GPU buffer is available */
}

DataVisCUDA::~DataVisCUDA() {
  m_wrapper.disconnect();
  destroyPBO();
}

void DataVisCUDA::init() {
  m_wrapper.init();
  createPBO();
  if (m_initial_image && (m_width > 0) && (m_height > 0)) {
    color3 *cpuBuff = new color3[m_width * m_height];
    loadPixels(cpuBuff);
    if (!m_wrapper.copyToGPU(cpuBuff, m_width, m_height)) {
      printf("Unable to copy image to GPU\n");
    }
    delete[] cpuBuff;
    cpuBuff = nullptr;
  }
  m_ready = true;
}

void DataVisCUDA::update() {
  if (!m_ready) {
    init();
  }
  color3 *buff = m_wrapper.map();
  m_image.buffer = buff;
  if (m_animate) {
    m_animate->update(&m_image);
  }
  m_wrapper.unmap();
}

void DataVisCUDA::textureReload() {
  update();
  m_texture->bind();
  // Read Texture data from PBO
  m_pbo->bind();
  m_texture->setData(QOpenGLTexture::RGB, QOpenGLTexture::UInt8,
                     (const void *)nullptr, &m_options);
  m_pbo->release();
}

void DataVisCUDA::createPBO() {
  destroyPBO(); // get rid of any old buffer

  // Create PBO
  int numBytes = sizeof(GLubyte) * 3 * m_width * m_height;
  m_pbo = new QOpenGLBuffer(
      QOpenGLBuffer::PixelUnpackBuffer); // Used for reading Texture data
  m_pbo->create();
  m_pbo->bind();
  m_pbo->allocate(numBytes);
  m_wrapper.connect(m_pbo->bufferId()); // Inform CUDA about PBO
  m_pbo->release();

  createTexture();
}

void DataVisCUDA::destroyPBO() {
  if (m_pbo) {
    m_pbo->release();
    delete m_pbo;
    m_pbo = nullptr;
  }
}
