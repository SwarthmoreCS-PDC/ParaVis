#pragma once

#include "mainwindow.h"
#include "dataVisCUDA.h"
#include <QApplication>
#include <QString>

class QTViewer{

  public:
    QTViewer(int argc, char* argv[], int w, int h, QString title);
    ~QTViewer();
    void setAnimation(DataVis* vis);
    int run();
  private:
     QApplication* m_app;
     MainWindow* m_window;
};
