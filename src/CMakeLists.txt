add_subdirectory(shaders)
add_subdirectory(common)

#General vis libraries but not too Qt heavy
target_sources(qtvis
   PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/timerCPU.cpp
    ${CMAKE_CURRENT_LIST_DIR}/dataVis.cpp
    ${CMAKE_CURRENT_LIST_DIR}/dataVisCPU.cpp
)

#Core Qt window stuff, some requring AutoMOC AutoUI
target_sources(qtvis
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/mainwindow.cpp
    ${CMAKE_CURRENT_LIST_DIR}/mypanelopengl.cpp
    ${CMAKE_CURRENT_LIST_DIR}/qtViewer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/mainwindow.ui
)
set_target_properties(qtvis PROPERTIES
  AUTOMOC ON
  AUTOUIC ON
)
