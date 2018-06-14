#pragma once
/* Nuclear option if Qt gives me any guff about
   including gl* functions in a class with Qt code.
   Just inherit this helper */
   
#include <QOpenGLFunctions_4_1_Core>

class QOGLHelper : protected QOpenGLFunctions_4_1_Core{
public:
  QOGLHelper(){
    initializeOpenGLFunctions();
  }

  ~QOGLHelper(){/*do nothing*/}
};
