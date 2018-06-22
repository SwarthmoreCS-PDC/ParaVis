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


add_subdirectory(common)

set(UTIL_HEADERS
  timerBase.h timerCPU.h
  dataVis.h
  dataVisCPU.h
  )

set(UTIL_SRC
  timerCPU.cpp
  dataVis.cpp
  dataVisCPU.cpp
  )

add_library(myutil ${UTIL_HEADERS} ${UTIL_SRC})

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

add_library(myvis ${SRC} ${SHDRS} ${MYQTFILES})
set(COMLIBS myvis myutil shapes ${OPENGL_LIBRARY}
Qt5::Core Qt5::Gui Qt5::OpenGL)

set(CPUDEMO_HDRS
  gradientVis.h
)
set(CPUDEMO_SRC
  gradientVis.cpp
)
add_library(democpu ${CPUDEMO_HDRS} ${CPUDEMO_SRC})
ADD_EXECUTABLE(cpuDemos main.cpp)
TARGET_LINK_LIBRARIES(cpuDemos democpu ${COMLIBS})

#get symlink_data macro
include(${CMAKE_SOURCE_DIR}/cmake_modules/helpers.cmake)
symlink_data(shaders *.glsl)

#for CUDA
FIND_PACKAGE(CUDA QUIET)
if(CUDA_FOUND)
  cuda_include_directories(${CUDA_INC} ${CMAKE_CURRENT_SOURCE_DIR})
  link_directories(${CUDA_SDK}/lib/)
  # CUDA 8 gets grumpy about deprecated archs
  if (CUDA_VERSION VERSION_GREATER "7.5")
    #CMake 3.7+
    CUDA_SELECT_NVCC_ARCH_FLAGS(ARCH_FLAGS Auto)
    LIST(APPEND CUDA_NVCC_FLAGS ${ARCH_FLAGS})
    #LIST(APPEND CUDA_NVCC_FLAGS "-arch=sm_30")
  endif()
endif()

if (CUDA_FOUND)
  add_library(cudaqt dataVisCUDA.cpp dataVisCUDA.h ${UTIL_HEADERS})

  set(GPU_UTIL_HEADERS
    handle_cuda_error.h
    timerBase.h timerGPU.h
    dataVis.h
    timerBase.h
    cudaWrapper.h
    dataVisCUDA.h
    )

  set(GPU_UTIL_SRC
    handle_cuda_error.cu
    timerGPU.cu
    cudaWrapper.cu
    )

  cuda_add_library(mycudautil ${GPU_UTIL_HEADERS} ${GPU_UTIL_SRC})

  cuda_add_library(cudademos
  juliaKernel.h rippleKernel.h userBufferKernel.h
  juliaKernel.cu rippleKernel.cu userBufferKernel.cu
  )

  set(CUDALIBS cudaqt mycudautil cudademos)

  ADD_EXECUTABLE(cudaDemos cudaDemos.cpp)
  TARGET_LINK_LIBRARIES(cudaDemos ${CUDALIBS} ${COMLIBS})
endif()

FIND_PACKAGE(Threads)
if(CMAKE_USE_PTHREADS_INIT)
  set(THREAD_DEMO_HDRS
    pthreadVis.h
  )
  set(THREAD_DEMO_SRC
    pthreadVis.cpp
  )
  if(APPLE)
    add_subdirectory(osxbarrier)
  endif()
  add_library(demothread ${THREAD_DEMO_HDRS} ${THREAD_DEMO_SRC})
  ADD_EXECUTABLE(threadDemos threadDemos.cpp)
  TARGET_LINK_LIBRARIES(threadDemos demothread ${COMLIBS} Threads::Threads )
  if(APPLE)
  TARGET_LINK_LIBRARIES(threadDemos osxbarrier)
  endif()
endif()
