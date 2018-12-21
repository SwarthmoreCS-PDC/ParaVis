#include "dataVis.h"
#include <QDebug>

DataVis::DataVis(int w, int h, int d)
    : m_width(w), m_height(h), m_depth(d),
      m_ready(false), m_texture(nullptr), m_initial_image(nullptr) {
   initCommon();
}

DataVis::DataVis(QString imgFileName): m_width(0), m_height(0), m_depth(1),
      m_ready(false), m_texture(nullptr), m_initial_image(nullptr) {
   m_initial_image = new QImage(imgFileName);
   if(m_initial_image->isNull()){
     qDebug()<< "Failed to open image: " << imgFileName;
     qDebug()<< "Color buffer size set to 0 by 0" << imgFileName;
   }
   m_width = m_initial_image->width();
   m_height = m_initial_image->height();
   initCommon();
}

void DataVis::initCommon(){
  m_image.height = m_height;
  m_image.width = m_width;
  m_image.depth = m_depth;
  m_image.buffer = nullptr;

  /* Allows image buffer with dimensions
     that are not powers of 2 to write
     to OpenGL textures properly */
  m_options.setAlignment(1);
}

DataVis::~DataVis() {
  delete m_texture;
  m_texture = nullptr;
  delete m_initial_image;
  m_initial_image = nullptr;
}

void DataVis::createTexture() {
  m_texture = new QOpenGLTexture(QOpenGLTexture::Target2D);
  // Create ID, allocate space for Texture
  m_texture->create();
  m_texture->bind();
  m_texture->setSize(m_width, m_height);
  m_texture->setFormat(QOpenGLTexture::RGB8_UNorm);
  m_texture->allocateStorage();
  QOpenGLTexture::Filter filt = QOpenGLTexture::Nearest;
  m_texture->setMinMagFilters(filt, filt);
  m_texture->setWrapMode(QOpenGLTexture::ClampToEdge);
}

void DataVis::loadPixels(color3* buff){
  if(!m_initial_image || m_initial_image->isNull()){
    qDebug()<< "Can't read from bad/missing initial image";
  }
  int off;
  QColor qclr;
  color3 clr3;
  for(int row=0; row<m_height; row++){
    for(int col=0; col<m_width; col++){
      off = row*m_width+col;
      qclr = m_initial_image->pixelColor(col, m_height-1-row);
      clr3.r = qclr.red();
      clr3.g = qclr.green();
      clr3.b = qclr.blue();
      buff[off] = clr3;
    }
  }
}
