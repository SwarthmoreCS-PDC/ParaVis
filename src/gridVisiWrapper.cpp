#include "gridVisiWrapper.h"
#include "dataVisCFunction.h"
#include <qtViewer.h>
#include <dataVis.h>

/*
 * initialize and run the 2D grid animation
 *   rows: the number of rows in the grid
 *   cols: the number of columns in the grid
 *   data: a pointer to application-specific data (type defined by programer)
 *   name: a name string for the visi
 *   update_func: name of your update function (matching c_update_t prototype)
 *   iters: if non-zero, run animation for iters steps (otherwise runs
 *          until explicitly exits)
 */
extern "C" void init_and_run_animation(int rows, int cols,
        void* data, c_update_t update_func,
        char *name, int iters)
{
     GridVisiWrapper wrapper(rows,cols,data,update_func,name);
     wrapper.run(iters);
}

GridVisiWrapper::GridVisiWrapper(int rows, int cols,
        void* data, c_update_t update_func,
        char *name){
    argc=1;
    argv[0] = new char[5];
    argv[0][0]='h';
    argv[0][1]='i';
    argv[0][2]='\0';
    viewer=new QTViewer(argc,argv,600,500,name);
    visi_grid=new DataVisCFunction(rows, cols, data, update_func);
    viewer->setAnimation(visi_grid);
}

GridVisiWrapper::~GridVisiWrapper(){
  delete viewer; viewer=nullptr;
  delete [] argv[0]; argv[0]=nullptr;
}

int GridVisiWrapper::run(int iters){
  if(iters > 0){
    return viewer->run(iters);
  }
  else{
    return viewer->run();
  }
}
