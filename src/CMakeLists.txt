add_library(myutil timerCPU.cpp dataVis.cpp dataVisCPU.cpp)
target_link_libraries(myutil PUBLIC inclib)

add_subdirectory(shaders)
add_subdirectory(common)

#required CMake options for QT Apps
#TODO: clean up this hot mess of global settings.
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(./)
set(CMAKE_CXX_FLAGS "--std=c++11 -g -Wall")
ADD_DEFINITIONS(${Qt5Widgets_DEFINITIONS})
SET(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
include_directories(
  ${Qt5Widgets_INCLUDE_DIRS}
  ${Qt5OpenGL_INCLUDE_DIRS}
  ${Qt5Multimedia_INCLUDE_DIRS})


#QT headers requiring MOC (meta object compiler)
set(QTHDRS
  ../include/mainwindow.h
  ../include/mypanelopengl.h
  )


#Run qt tools to auto generate C++ compatible files
QT5_WRAP_CPP(QTHDRS_MOC ${QTHDRS})
QT5_WRAP_UI(QTFORMS_HDRS mainwindow.ui)

add_library(myvis
  mainwindow.cpp mypanelopengl.cpp qtViewer.cpp
${QTHDRS_MOC} ${QTFORMS_HDRS})
target_link_libraries(myvis PUBLIC inclib)
