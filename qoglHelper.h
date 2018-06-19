#pragma once

/* Nuclear option if Qt gives me any guff about
   including gl* functions in a class with Qt code.
   Just inherit this helper */

/*
   This is one spot where we declare we want an OpenGL 4.1
   Core context. Other spots include
       qtViewer.h (currently unused)
       glsl shader code (# version 410)
*/
#include <QOpenGLFunctions_4_1_Core>

class QOGLHelper : protected QOpenGLFunctions_4_1_Core{
public:
  QOGLHelper(){
    initializeOpenGLFunctions();
  }

  ~QOGLHelper(){/*do nothing*/}
};
