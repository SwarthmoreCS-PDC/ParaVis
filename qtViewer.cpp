#include "qtViewer.h"
#include "mypanelopengl.h"
#include "dataVis.h"
#include <QSurfaceFormat>
#include <iostream>
#include <string>


QTViewer::QTViewer(int argc, char* argv[], int w, int h, QString title){
  /* OpenGL format must be set before launching application
     This is one spot where we declare we want an OpenGL 4.1
     Core context. Other spots include
       qoglHelper.h (currently unused)
       glsl shader code (# version 410)
  */
  QSurfaceFormat format;
  format.setVersion(4, 1);
  format.setProfile(QSurfaceFormat::CoreProfile);
  QSurfaceFormat::setDefaultFormat(format);

  /* Create the app, set the title and show the UI */
  m_app = new QApplication(argc, argv);
  m_window = new MainWindow();
  m_window->setWindowTitle(title);
  m_window->show();
}

QTViewer::~QTViewer(){
  delete m_window; m_window=nullptr;
  delete m_app; m_app=nullptr;
}

void QTViewer::setAnimation(DataVis* vis){
  /* Pass info onto window, who will pass it on to
     the opengl panel */
  m_window->setAnimation(vis);
}

int QTViewer::run(){
  return m_app->exec();
}
