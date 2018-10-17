#pragma once

#include "qtViewer.h"

/* QApplication and QTViewer require that argc and argv
   constructor inputs have the lifetime of the object.
   This sometimes causes problems when argc and argv
   are not needed or readily available. This class provides
   a thin wrapper around QTViewer that provides safe defaults
   for argc, argv */
class QTSafeViewer {

public:
  QTSafeViewer(int w = 600, int h = 500, QString title = "Demo");
  ~QTSafeViewer();
  /* Connect a user specified visualization to viewer
     Must be called before calling run  */
  inline void setAnimation(DataVis *vis) { m_viewer->setAnimation(vis); }

  /* Start the animation and event loop for the Viewer
 Viewer will not return until user quits application
 or maxSteps reached if maxSteps is a value >=0  */
  inline int run(int maxSteps = -1) { return m_viewer->run(maxSteps); }

private:
  QTViewer *m_viewer;
  int m_argc;
  char *m_argv[1];
};
