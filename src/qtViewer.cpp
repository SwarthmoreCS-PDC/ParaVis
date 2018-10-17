#include "qtViewer.h"
#include "dataVis.h"
#include "mypanelopengl.h"
#include <QSurfaceFormat>
#include <iostream>
#include <string>

QTViewer::QTViewer(int argc, char *argv[], int w, int h, QString title)
    : m_argc(argc) {
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
  /* Why m_argc? Warning: The data referred to by argc and argv must stay valid
  for the entire lifetime of the QApplication object. In addition, argc must be
  greater than zero and argv must contain at least one valid character string.
  http://doc.qt.io/qt-5/qapplication.html#QApplication
  */
  m_app = new QApplication(m_argc, argv);
  m_window = new MainWindow();
  m_window->setWindowTitle(title);
  m_window->show();
  m_window->resize(w, h);
}

QTViewer::~QTViewer() {
  delete m_window;
  m_window = nullptr;
  delete m_app;
  m_app = nullptr;
}

void QTViewer::setAnimation(DataVis *vis) {
  /* Pass info onto window, who will pass it on to
     the opengl panel */
  m_window->getGLWidget()->setAnimation(vis);
}

int QTViewer::run(int maxSteps) {
  m_window->getGLWidget()->setMaxSteps(maxSteps);
  return m_app->exec();
}
