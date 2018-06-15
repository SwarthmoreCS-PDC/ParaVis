#pragma once

#include "mainwindow.h"
#include "dataVisCUDA.h"
#include <QApplication>
#include <QString>

/* A wrapper around a standard Qt Application with a OpenGL panel an
   a control panel. There is no need for a typical user to modify this
   class */
class QTViewer{

  public:
    /* Create a new GUI
       argc: number of command line arguments
       argv: command line arguments. These are not used by QtViewer
       w:  width of OpenGL display in pixels
       h:  height of OpenGL display in pixels
       TODO: h/w not yet implemented
       title: Optional title of GUI applicaiton
    */
    QTViewer(int argc, char* argv[], int w, int h, QString title="Demo");
    ~QTViewer();

    /* Connect a user specified visualization to viewer
       Must be called before calling run  */
    void setAnimation(DataVis* vis);

    /* Start the animation and event loop for the Viewer
       Viewer will not return until user quits application */
    int run();

  private:
     QApplication* m_app;   /* Basic Qt Application */
     MainWindow* m_window;  /* Specific Layout from mainwindow.* */
};
