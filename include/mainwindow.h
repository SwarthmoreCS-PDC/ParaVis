#pragma once

#include <QMainWindow>
#include "mypanelopengl.h"
#include "dataVis.h"

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

  /* connect a user supplied visualization to the
     openGL panel */
  void setAnimation(DataVis* vis);

private:
  Ui::MainWindow *ui; /* auto-generated ui from mainwindow.ui */
};
