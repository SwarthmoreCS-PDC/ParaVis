#pragma once

#include <QOpenGLFunctions_4_1_Core>

class QOGLHelper : protected QOpenGLFunctions_4_1_Core{
public:
  QOGLHelper(){
    initializeOpenGLFunctions();
  }

  ~QOGLHelper(){/*do nothing*/}
};
