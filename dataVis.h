#pragma once

#include <QOpenGLTexture>
#include "imageBuffer.h"

/* The DataVis class is the primary connection between
   the animation library and user provided code that
   colors an ImageBuffer object. Users will typically
   Implement their own class that inherits from the DataVis class,
   or a specialized subclass of the DataVis class.

   Users will primarily need to focus on providing an
   implementation of the update() method that computes
   new color values for the underlying ImageBuffer m_image.

   CUDA users will need to take a slightly different approach,
   and use the provided DataVisCUDA class as their primary
   implementation while providing an implementation of the
   Animator interface, which performs a similar update of the
  image buffer.
  */


class DataVis {

public:
  /* Construct a new visualization with the dimensions given */
  // Depth d currently not used
  DataVis(int w, int h, int d=1);
  virtual ~DataVis();

  /* Updates the colors in the ImageBuffer. Typically
     implemented by the user in a derived class.
     The DataVisCUDA class provides an implementation of
     this method, but further defers the update of
     the color buffer to an Animator class that the
     user must implement */
  virtual void update() = 0;

  /* Typically implemented by a subclass for a given
     parallel framework, this method, copies the data
     from the Image Buffer to the underlying OpenGL
     texture */
  virtual void textureReload() = 0;

  /* Make the undelying OpenGL texture the current
     active texture for rendering */
  inline void bind() { m_texture->bind(); }

protected:
  /* Dimensions of the Image Buffer */
  int m_width, m_height, m_depth;
  /* Set to true once the Image Buffer has been allocated */
  bool m_ready;
  /* The underlying OpenGL texture representation of the
     Image Buffer */
  QOpenGLTexture *m_texture;
  /* Color data populated by the user and eventually
     displayed on the screen */
  ImageBuffer m_image;

  /* A helper method to setup the m_texture object */
  void createTexture();

};
