cmake_minimum_required(VERSION 3.7)

FIND_PACKAGE(OpenGL REQUIRED)  #Graphics API


#for QT Window widgets
FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE(Qt5Gui REQUIRED)
FIND_PACKAGE(Qt5OpenGL REQUIRED)

#required CMake options for QT Apps
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


add_library(inclib INTERFACE)
target_include_directories(inclib INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

set(UTIL_HEADERS
  include/timerBase.h
  include/timerCPU.h
  include/dataVis.h
  include/dataVisCPU.h
  )

set(UTIL_SRC
  timerCPU.cpp
  dataVis.cpp
  dataVisCPU.cpp
  )


add_library(myutil ${UTIL_HEADERS} ${UTIL_SRC})
target_link_libraries(myutil PUBLIC inclib)



#QT headers requiring MOC (meta object compiler)
set(QTHDRS
  include/mainwindow.h
  include/mypanelopengl.h
  )

#window design files
set(QTFORMS mainwindow.ui)

#Run qt tools to auto generate C++ compatible files
QT5_WRAP_CPP(QTHDRS_MOC ${QTHDRS})
QT5_WRAP_UI(QTFORMS_HDRS ${QTFORMS})
SET(MYQTFILES ${QTHDRS_MOC} ${QTFORMS_HDRS})

#normal source files
set(SRC
  mainwindow.cpp
  mypanelopengl.cpp
  qtViewer.cpp
)

set(SHDRS
  include/qtViewer.h
  include/qoglHelper.h
  include/color3.h
  include/imageBuffer.h
)

add_library(myvis ${SRC} ${SHDRS} ${MYQTFILES})
target_link_libraries(myvis PUBLIC inclib)


set(COMLIBS myvis myutil shapes ${OPENGL_LIBRARY}
Qt5::Core Qt5::Gui Qt5::OpenGL)

add_subdirectory(src)
add_subdirectory(demos)

#for CUDA
FIND_PACKAGE(CUDA QUIET)
if(CUDA_FOUND)
  cuda_include_directories(${CUDA_INC} ${CMAKE_SOURCE_DIR}/include)
  link_directories(${CUDA_SDK}/lib/)
  # CUDA 8 gets grumpy about deprecated archs
  if (CUDA_VERSION VERSION_GREATER "7.5")
    #CMake 3.7+
    CUDA_SELECT_NVCC_ARCH_FLAGS(ARCH_FLAGS Auto)
    LIST(APPEND CUDA_NVCC_FLAGS ${ARCH_FLAGS})
  endif()

  add_subdirectory(src/cuda)
  add_subdirectory(demos/cuda)
endif()


FIND_PACKAGE(Threads)
if(CMAKE_USE_PTHREADS_INIT)
  if(APPLE)
    add_subdirectory(src/osx)
  endif()
  add_subdirectory(demos/pthreads)
endif()

find_package(OpenMP)
#TODO: Apple support for openMP is weird
#port install libomp, manually set OpenMP_CXX_FLAGS/LIB_NAMES
if(OpenMP_FOUND OR OPENMP_FOUND)
  if(NOT TARGET OpenMP::OpenMP_CXX)
      add_library(OpenMP_TARGET INTERFACE)
      add_library(OpenMP::OpenMP_CXX ALIAS OpenMP_TARGET)
      target_compile_options(OpenMP_TARGET INTERFACE ${OpenMP_CXX_FLAGS})
      find_package(Threads REQUIRED)
      target_link_libraries(OpenMP_TARGET INTERFACE Threads::Threads)
      target_link_libraries(OpenMP_TARGET INTERFACE ${OpenMP_CXX_FLAGS})
  endif()
  add_subdirectory(demos/openMP)
endif()
