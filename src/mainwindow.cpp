#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() {
  delete ui;
  ui = nullptr;
}

MyPanelOpenGL *const MainWindow::getGLWidget() { return ui->panelGL; }
