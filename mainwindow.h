#pragma once

#include <QMainWindow>
#include "mypanelopengl.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  /*TODO: rename */
  MyPanelOpenGL* getGLThing(){ return qtgoo; }

private:
  Ui::MainWindow *ui;
  MyPanelOpenGL* qtgoo;
};
