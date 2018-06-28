add_subdirectory(shaders)
add_subdirectory(common)

#General vis libraries but not too Qt heavy
target_sources(qtvis
   PRIVATE
    src/timerCPU.cpp
    src/dataVis.cpp
    src/dataVisCPU.cpp
)

#Core Qt window stuff, some requring AutoMOC AutoUI
target_sources(qtvis
  PRIVATE
    src/mainwindow.cpp
    src/mypanelopengl.cpp
    src/qtViewer.cpp
    src/mainwindow.ui
    include/mainwindow.h
    include/mypanelopengl.h
)
set_target_properties(qtvis PROPERTIES
AUTOMOC ON
AUTOUIC ON)
