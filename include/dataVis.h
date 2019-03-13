#pragma once

#include "imageBuffer.h"

#ifdef _WIN32
#include<windows.h>
#endif

#include <QOpenGLPixelTransferOptions>
#include <QOpenGLTexture>

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
  DataVis(int w, int h, int d = 1);

  /* Construct a new visualization using the provided image file
     name for the initial dimensions and colors */
  DataVis(QString imgFileName);

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

  /* return a shallow copy of the image buffer. Usually users
     should just subclass DataVis and write their own update
     method to update the image, but in some cases, for example, when
     working with C-style functions, it may be necessary to have
     direct access to the image buffer */
  inline ImageBuffer getImageData() { return m_image; }

protected:
  /* Dimensions of the Image Buffer */
  int m_width, m_height, m_depth;

  /* Set to true once the Image Buffer has been allocated */
  bool m_ready;

  /* The underlying OpenGL texture representation of the
     Image Buffer */
  QOpenGLTexture *m_texture;

  QOpenGLPixelTransferOptions m_options;

  /* Color data populated by the user and eventually
     displayed on the screen */
  ImageBuffer m_image;

  /* An optional image (e.g., png/jpeg file) that can be
     the source of colors for the initial color buffer */
  QImage* m_initial_image;

  /* common constructor code */
  void initCommon();

  /* A helper method to setup the m_texture object */
  void createTexture();

  /* read pixels from initial image and write to supplied
     color buffer. Assumes space is already allocated
     on CPU for buff in row major order */
  void loadPixels(color3* buff);

};
