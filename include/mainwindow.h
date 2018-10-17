#pragma once

#include "dataVis.h"
#include "mypanelopengl.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

/* A wrapper class for the UI sketched out in
   mainwindow.ui using QtCreator and constructed
   automatically via the build system. Customized
   slightly to add support for the setAnimation
   method. A typical user should never need to modify
   this class. */
class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  MyPanelOpenGL *const getGLWidget();

private:
  Ui::MainWindow *ui; /* auto-generated ui from mainwindow.ui */
};
