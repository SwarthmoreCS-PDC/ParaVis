cmake_minimum_required(VERSION 2.8.11)

set(CMAKE_CXX_FLAGS "--std=c++11 -g -Wall")

set (CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules) #for FindGLEW.cmake


FIND_PACKAGE(OpenGL REQUIRED) #for graphics

#required CMake options for QT Apps
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Threads REQUIRED)

#for CUDA
find_package(CUDA QUIET REQUIRED)
cuda_include_directories(${CUDA_INC} ${CMAKE_CURRENT_SOURCE_DIR})
link_directories(${CUDA_SDK}/lib/)
# CUDA 8 gets grumpy about deprecated archs
if (CUDA_VERSION VERSION_GREATER "7.5")
  #CMake 3.7
  #CUDA_SELECT_NVCC_ARCH_FLAGS(ARCH_FLAGS Auto)
  LIST(APPEND CUDA_NVCC_FLAGS "-arch=sm_30")
endif()

#get symlink_data macro
include(${CMAKE_SOURCE_DIR}/cmake_modules/helpers.cmake)
include_directories(./)


#for window widgets
FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5Gui REQUIRED)
FIND_PACKAGE(Qt5OpenGL REQUIRED)
FIND_PACKAGE(Qt5Multimedia REQUIRED)
ADD_DEFINITIONS(${Qt5Widgets_DEFINITIONS})
SET(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
include_directories(
  ${Qt5Widgets_INCLUDE_DIRS}
  ${Qt5OpenGL_INCLUDE_DIRS}
  ${Qt5Multimedia_INCLUDE_DIRS})

set(UTIL_HEADERS
  timerBase.h timerCPU.h
  dataVisCUDA.h
  )

set(UTIL_SRC
  timerCPU.cpp
  dataVisCUDA.cpp
  )

set(GPU_UTIL_HEADERS
  handle_cuda_error.h
  timerBase.h timerGPU.h
  )

set(GPU_UTIL_SRC
  handle_cuda_error.cu
  timerGPU.cu
  )

add_library(myutil ${UTIL_HEADERS} ${UTIL_SRC})
cuda_add_library(mycudautil ${GPU_UTIL_HEADERS} ${GPU_UTIL_SRC})

set(MYLIBS mycudautil myutil)
set(GLLIBS ${OPENGL_LIBRARY})

symlink_data(shaders *.glsl)

add_subdirectory(common)

cuda_add_library(cudawrapper
  cudaWrapper.h juliaKernel.h rippleKernel.h userBufferKernel.h
  cudaWrapper.cu juliaKernel.cu rippleKernel.cu userBufferKernel.cu
  )

#QT headers requiring MOC (meta object compiler)
set(QTHDRS
  mainwindow.h
  mypanelopengl.h
  )

#window design files
set(QTFORMS mainwindow.ui)

#Run qt tools to auto generate C++ compatible files
QT5_WRAP_CPP(QTHDRS_MOC ${QTHDRS})
QT5_WRAP_UI(QTFORMS_HDRS ${QTFORMS})
SET(MYQTFILES ${QTHDRS_MOC} ${QTFORMS_HDRS})

#normal source files
set(SRC
  main.cpp
  mainwindow.cpp
  mypanelopengl.cpp
  qtViewer.cpp
)

set(SHDRS
  qtViewer.h
  qoglHelper.h
  color3.h
  imageBuffer.h
)

ADD_EXECUTABLE(interop ${SRC} ${SHDRS} ${MYQTFILES})

TARGET_LINK_LIBRARIES(interop
  ${MYLIBS} cudawrapper libcommon mycudautil
  ${GLLIBS}
  Qt5::Core Qt5::Gui Qt5::OpenGL)
