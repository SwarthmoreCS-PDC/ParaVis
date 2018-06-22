#include "pthreadVis.h"
#include <pthread.h>


void *threadUpdate(void* info){
  threadInfo* tinfo = (threadInfo*) info;
  int off;
  int w,h;
  int rowstart, rowstop, maxrows;
  unsigned char val;
  w= tinfo->img->width;
  h= tinfo->img->height;

  maxrows = h/tinfo->nThreads;
  if(h%tinfo->nThreads >0) { maxrows++; }
  rowstart=maxrows*tinfo->id;
  rowstop=rowstart+maxrows;
  if(rowstop > h) { rowstop = h; }

  for(int r=rowstart; r<rowstop; r++){
    for(int c=0; c<w; c++){
      off = r*w+c;
      val = (unsigned char) (128. * r /maxrows);
      val = (val+tinfo->ticks)%128;
      tinfo->img->buffer[off].r=val;
      tinfo->img->buffer[off].g=0;
      tinfo->img->buffer[off].b=128-val;
    }
  }
  return nullptr;
}

PThreadVis::PThreadVis(int numThreads, int w, int h, int d) :
   DataVisCPU(w,h,d), m_ticks(0), m_numThreads(numThreads){
   /* do nothing */
};

PThreadVis::~PThreadVis(){
  /* do nothing */
}

void PThreadVis::update() {
  pthread_t* threads;
  threadInfo* tinfo;
  int i;
  threads = new pthread_t[m_numThreads];
  tinfo = new threadInfo[m_numThreads];
  tinfo[0].nThreads=m_numThreads;
  tinfo[0].ticks=m_ticks;
  tinfo[0].img=&m_image;
  for(i=0;i<m_numThreads;i++){
    tinfo[i]=tinfo[0];
    tinfo[i].id=i;
    pthread_create(&threads[i], nullptr, threadUpdate, (void*)&tinfo[i]);
  }
  for(i=0;i<m_numThreads;i++){
    pthread_join(threads[i], nullptr);
  }
  m_ticks += 1;
  delete [] threads; threads=nullptr;
  delete [] tinfo; tinfo=nullptr;
}
