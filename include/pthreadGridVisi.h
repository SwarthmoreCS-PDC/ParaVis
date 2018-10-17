#ifndef _pthreadgridVisi_h_
#define _pthreadgridVisi_h_

#include "cgridvisi.h" // definition of c_update_t function pointer type
#include "color3.h"

/* exported typedef for internal state passed between libray functionns */
struct visi_pthread_struct;
typedef struct visi_pthread_struct *visi_pthread_handle;

/*
 * To use this interface you need to first define:
 * ----------------------------------------------
 *  a struct type containing fields for application-specific state
 *  that will be passed to each thrad via pthread_create.  One field
 *  in this struct should to be the (color3 *) buffer returned by
 *  get_buff_pthread_animation.  This is the buffer used by threads to
 *  update the visualization.
 *
 * The main program control flow should look like:
 * ----------------------------------------------
 *  (1) initailize all program state (in fields of struct variable)
 *      including any pthread synch primatives
 *  (2) main thread: call init_pthread_animation (only one thread should call)
 *  (3) main thread: call get_buff_pthread_animation to get the color3 buff
 *      (only one thread should call this)
 *  (4) create worker threads (call pthread_create), each should:
 *       (a) init any thread-specific state
 *       (b) loop:
 *           do next computation step
 *           update color3 buf
 *           call draw_pthread_animation
 *  (5) main thread: call run_pthread_animation to run the visi animation
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
extern visi_pthread_handle
init_pthread_animation(int num_tids, int rows, int cols, char *name, int iters);
/*
 *  get the color3 buffer associated with a visualization
 *   handle:  a handle to a visualization
 *   returns: pointer to color3 buffer for the visi, or NULL on error
 */
extern color3 *get_buff_pthread_animation(visi_pthread_handle handle);

/*
 * notify the visi library that a thread's update to a buffer is ready
 * (called by each thread after it updates its portion of the buffer
 * to reflect the next computation step)
 */
extern void draw_pthread_animation(visi_pthread_handle handle);

/*
 * runs the pthread animation: called by all threads in their main loop
 *   visi_info:  value returned by call to init_pthread_animation
 *   iters: run for specified number of iterations, or if 0 run forever
 */
extern void run_pthread_animation(visi_pthread_handle visi_info, int iters);

#endif
