#include "mainwindow.h"
#include "mypanelopengl.h"
#include <QApplication>
#include <QSurfaceFormat>
#include <iostream>
#include <string>
#include <QString>

int main(int argc, char *argv[]) {
  /*OpenGL format must be set before launching application*/
  QSurfaceFormat format;
  format.setVersion(4, 1);
  format.setProfile(QSurfaceFormat::CoreProfile);
  QSurfaceFormat::setDefaultFormat(format);

  /* Create Application and Main Window */
  QApplication a(argc, argv);
  MainWindow w;
  QString title = "SnickerDoodle";
  w.setWindowTitle(title);
  w.show();

  /* Get object for OGL interaction */
  MyPanelOpenGL* blob = w.getGLThing();
  blob->doSomething();

  /* Run app */
  int res = a.exec();

  /* Cleanup */
  std::cout << "Exiting" << std::endl;
  return res;
}
