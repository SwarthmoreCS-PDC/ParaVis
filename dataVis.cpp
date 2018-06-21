#include "dataVis.h"

DataVis::DataVis(int w, int h, int d):
 m_width(w), m_height(h), m_depth(d),
   m_ready(false), m_texture(nullptr) {
     m_image.height=h;
     m_image.width=w;
     m_image.depth=d;
     m_image.buffer=nullptr;

     /* Allows image buffer with dimensions
        that are not powers of 2 to write
        to OpenGL textures properly */
     m_options.setAlignment(1);
   }

DataVis::~DataVis(){
  delete m_texture;
  m_texture = nullptr;
}

void DataVis::createTexture(){
  m_texture = new QOpenGLTexture(QOpenGLTexture::Target2D);
  // Create ID, allocate space for Texture
  m_texture->create();
  m_texture->bind();
  m_texture->setSize(m_width, m_height);
  m_texture->setFormat(QOpenGLTexture::RGB8_UNorm);
  m_texture->allocateStorage();
  QOpenGLTexture::Filter filt = QOpenGLTexture::Linear;
  m_texture->setMinMagFilters(filt, filt);
  m_texture->setWrapMode(QOpenGLTexture::ClampToEdge);
}
