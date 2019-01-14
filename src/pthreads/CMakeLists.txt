#General vis libraries but not too Qt heavy
target_sources(qtvis
   PRIVATE
   ${CMAKE_CURRENT_LIST_DIR}/pthreadGridVisi.cpp
   ${CMAKE_CURRENT_LIST_DIR}/dataVisPThreads.cpp
)
