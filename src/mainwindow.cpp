#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; ui=nullptr; }

void MainWindow::setAnimation(DataVis* vis){
  /* name of OpenGL panel is in mainwindow.ui
     Build system looks at this file, and creates
     ui_mainwindow.h file with named objects */
  ui->panelGL->setAnimation(vis);
}

void MainWindow::setMaxSteps(int steps){
  ui->panelGL->setMaxSteps(steps);
}
