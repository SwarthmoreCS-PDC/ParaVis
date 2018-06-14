#include "qtViewer.h"
#include "dataVisCUDA.h"
#include "juliaKernel.h"
#include "rippleKernel.h"
#include "userBufferKernel.h"
#include <iostream>


int main(int argc, char *argv[]) {
  /* TODO: use width, height to control size of window */
  QTViewer viewer(argc, argv, 10, 10, "SnickerDoodle");

  /* TODO: generalize this class */
  DataVisCUDA* vis = new DataVisCUDA(1000,1000);
  //Animator* kern = new JuliaKernel(-0.8,0.156);
  //Animator* kern = new RippleKernel();
  Animator* kern = new UserBufferKernel(1000,1000);

  vis->setAnimator(kern);
  viewer.setAnimation(vis);

  int res = viewer.run();
  delete kern; kern=nullptr;
  return res;
}
