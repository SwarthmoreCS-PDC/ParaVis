#ifndef _gridVisi_h_
#define _gridVisi_h_

#include <color3.h>

/*
 * To use this interface you need to first define:
 *
 * (1) struct appl_data containing all application-specific needs to define
 *     all application-specific state
 *
 * (2) implement an application-specific function that matches the
 *     c_update_t function prototype def:
 *        void your_func_name(color3 *buff, void *app_data);
 *
 *     this function implements the main application functionality
 *     and updates the visi grid.  Its main flow should be something like:
 *        (a) preform the next computation step
 *        (b) update the image grid to reflect this computation step
 *
 * Your main program control flow should look like:
 *  (1) initialize all program state (in struct appl_data variable)
 *  (2) call init_and_run_animation (pass appl_data and c_update function)
 */

/* function pointer type (a prototype type def) for the top-level program
 * function that will perform the computation and update the imagebuffer
 * based on your particular application.
 * (the update method of the gridVisi will call this function)
 * note: the image buffer coordinate (0,0) is the bottom left
 *
 * This defines the function prototype type as:
 *   void func_name(color3 *buff, struct appl_data *data);
 *     buff: the image buffer to update
 *     app_data: a struct to any application specific data needed
 */
typedef void (*c_update_t)(color3 *buff, void *app_data);

/*  A C wrapper around the C++ library that runs the animation.
    (implementation in gridVisiWrapper.cpp)

    rows, cols: dimensions of color buffer
    app_data: a struct to any application specific data
              this will be passed as the second argument to update_func
    update_func: A function pointer described above
    name: Display name of animation.
    iters: Max number of iterations to run. If iters<=0,
           the animation runs indefinitely until user presses
           quit button, CTRL-C, or closes the application
*/
void init_and_run_animation(int rows, int cols, void *app_data,
                            c_update_t update_func, char *name, int iters);
#endif
