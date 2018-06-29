cmake_minimum_required(VERSION 3.11)
project(qtParallelVis LANGUAGES CXX)
#TODO: where does wall , -g go now?
#set(CMAKE_CXX_FLAGS "--std=c++11 -g -Wall")

#Graphics API
FIND_PACKAGE(OpenGL REQUIRED)

#for QT Window widgets
FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE(Qt5Gui REQUIRED)
FIND_PACKAGE(Qt5OpenGL REQUIRED)

#link this interface library to any target needing to find include path
add_library(inclib INTERFACE)
target_include_directories(inclib
  INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_compile_features(inclib
  INTERFACE
    cxx_nullptr
)


#The primary libary. Sources can be added incrementally
add_library(qtvis "")
target_link_libraries(qtvis PUBLIC inclib Qt5::OpenGL OpenGL::GL)

#Primary library and demos
add_subdirectory(src)

#for CUDA
include(CheckLanguage)
check_language(CUDA)
if(CMAKE_CUDA_COMPILER)
  enable_language(CUDA)
  #CUDA Specific libraries/demos
  #Build a separate qtviscuda library that only needs
  #to be linked into cuda applications
  add_subdirectory(src/cuda)
  #Sample cuda demos linking qtvis and qtviscuda
  add_subdirectory(demos/cuda)
else()
  message(STATUS
  "Could not find CUDA, set CMAKE_CUDA_COMPILER to full path to nvcc if you think this is an error")
  #Optionally, add path to nvcc to PATH env variable
endif()

#[[
#not used in favor of new Cmake3 CUDA support
#TODO: setting arch flags??
FIND_PACKAGE(CUDA QUIET)
if(CUDA_FOUND)
  cuda_include_directories(${CUDA_INC} ${CMAKE_SOURCE_DIR}/include)
  set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS} --std=c++11 -g)
  link_directories(${CUDA_SDK}/lib/)
  # CUDA 8 gets grumpy about deprecated archs
  if (CUDA_VERSION VERSION_GREATER "7.5")
    #CMake 3.7+
    CUDA_SELECT_NVCC_ARCH_FLAGS(ARCH_FLAGS Auto)
    LIST(APPEND CUDA_NVCC_FLAGS ${ARCH_FLAGS})
  endif()

  #CUDA Specific libraries/demos
  add_subdirectory(src/cuda)
  target_link_libraries(qtvis INTERFACE mycudautil)
  add_subdirectory(demos/cuda)
endif()
]]

#for PThreads
FIND_PACKAGE(Threads)
if(CMAKE_USE_PTHREADS_INIT)
  target_link_libraries(qtvis INTERFACE Threads::Threads)
  if(APPLE)
    #compile separate libary for pthread_barrier on osx
    add_subdirectory(src/osx)
  endif()
  #include pthread demos
  add_subdirectory(demos/pthreads)
endif()

find_package(OpenMP)
#TODO: Apple support for openMP is weird
#port install libomp, manually set OpenMP_CXX_FLAGS/LIB_NAMES
if(OpenMP_FOUND OR OPENMP_FOUND)
  #Add some boilerplate to make OpenMP support on Cmake 3.1 look more
  #like CMake 3.7+
  if(NOT TARGET OpenMP::OpenMP_CXX)
      add_library(OpenMP_TARGET INTERFACE)
      add_library(OpenMP::OpenMP_CXX ALIAS OpenMP_TARGET)
      target_compile_options(OpenMP_TARGET INTERFACE ${OpenMP_CXX_FLAGS})
      find_package(Threads REQUIRED)
      target_link_libraries(OpenMP_TARGET INTERFACE Threads::Threads)
      target_link_libraries(OpenMP_TARGET INTERFACE ${OpenMP_CXX_FLAGS})
  endif()
  #include openmp demos
  target_link_libraries(qtvis INTERFACE OpenMP::OpenMP_CXX)
  add_subdirectory(demos/openMP)
endif()

add_subdirectory(demos)
