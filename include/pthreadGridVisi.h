#ifndef _pthreadgridVisi_h_
#define _pthreadgridVisi_h_

#include "cgridvisi.h"
#include "color3.h"

#ifdef __APPLE__
#include <osx/pthread_barrier.h>
#endif

/*
 * To use this interface you need to first define:
 * ----------------------------------------------
 *  a struct type containing fields for application-specific state
 *  that will be passed to each thread via pthread_create.  One field
 *  in this struct should to be the (color3 *) buffer returned by
 *  get_buff_pthread_animation.  This is the buffer used by threads to
 *  update the visualization.
 *
 * The main program control flow should look like:
 * ----------------------------------------------
 *  (1) initialize all program state (in fields of struct variable)
 *      including any pthread synch primitives
 *  (2) main thread: call init_pthread_animation (only one thread should call)
 *  (3) main thread: call get_animation_buffer to get the color3 buff
 *      (only one thread should call this)
 *  (4) create worker threads (call pthread_create), each should:
 *       (a) init any thread-specific state
 *       (b) loop:
 *           do next computation step
 *           update color3 buf
 *           call draw_ready
 *  (5) main thread: call run_animation to run the visi animation
 *                   (only one thread should call this)
 *  (6) wait for worker threads to exit, then clean-up
 */

/* initialize the visualization:
 * this should only be called once (by one thread)
 *
 *     num_tids: total number of threads participating in the computation
 *     rows: number of rows
 *     cols: number of cols
 *     name: name for visi window
 *     iters: run for specified number of iterations, or if 0 run forever
 *     returns: a visi_pthread_handle or NULL on error
 */
extern visi_handle init_pthread_animation(int num_tids, int rows, int cols,
                                          char *name, int iters);

#endif
