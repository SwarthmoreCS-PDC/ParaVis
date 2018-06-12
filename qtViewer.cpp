#include "qtViewer.h"
#include "mypanelopengl.h"
#include "dataVisCUDA.h"
#include <QSurfaceFormat>
#include <iostream>
#include <string>


QTViewer::QTViewer(int argc, char* argv[], int w, int h, QString title){
  /*OpenGL format must be set before launching application*/
  QSurfaceFormat format;
  format.setVersion(4, 1);
  format.setProfile(QSurfaceFormat::CoreProfile);
  QSurfaceFormat::setDefaultFormat(format);

  m_app = new QApplication(argc, argv);
  m_window = new MainWindow();
  m_window->setWindowTitle(title);
  m_window->show();
}

QTViewer::~QTViewer(){
  delete m_window; m_window=nullptr;
  delete m_app; m_app=nullptr;
}

void QTViewer::setAnimation(DataVisCUDA* vis){
  m_window->getGLThing()->setVisulization(vis);
}

int QTViewer::run(){
  return m_app->exec();
}
