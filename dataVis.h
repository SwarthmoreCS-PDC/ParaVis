#pragma once

#include <QOpenGLTexture>
#include "imageBuffer.h"

class DataVis {

public:
  // Depth d currently not used
  DataVis(int w, int h, int d=1);
  virtual ~DataVis();

  virtual void update() = 0;

  virtual void textureReload() = 0;

  inline void bind() { m_texture->bind(); }

protected:
  int m_width, m_height, m_depth;
  bool m_ready;
  QOpenGLTexture *m_texture;
  ImageBuffer m_image;

  void createTexture();

};
