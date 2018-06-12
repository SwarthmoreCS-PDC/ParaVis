#include "qtViewer.h"
#include "dataVisCUDA.h"
#include <iostream>


int main(int argc, char *argv[]) {
  /* TODO: use width, height to control size of window */
  QTViewer viewer(argc, argv, 10, 10, "SnickerDoodle");

  /* TODO: generalize this class */
  DataVisCUDA* vis = new DataVisCUDA(1000,1000);
  viewer.setAnimation(vis);

  return viewer.run();
}
