#Core Qt window stuff, some requring AutoMOC AutoUI
target_sources(qtvis
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/mainwindow.h
    ${CMAKE_CURRENT_LIST_DIR}/mypanelopengl.h
)
