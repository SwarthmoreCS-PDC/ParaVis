cmake_minimum_required(VERSION 3.11)

#CXX used for most of project, C for OSX pthread extensions
project(qtParallelVis VERSION 0.1 LANGUAGES CXX C )

#CUDA CMAKE ARCHITECTURE POLICY CMAKE >= 3.18
if(POLICY CMP0104)
  cmake_policy(SET CMP0104 NEW)
endif()

#to switch betweeen release/debug builds
#cmake -DCMAKE_BUILD_TYPE=<Release/Debug/RelWithDebInfo/MinSizeRel> ..

#Graphics API
FIND_PACKAGE(OpenGL REQUIRED)

#for QT Window widgets
FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE(Qt5Gui REQUIRED)
FIND_PACKAGE(Qt5OpenGL REQUIRED)

#link this interface library to any target needing to find include path
add_library(compile_info INTERFACE)
target_include_directories(compile_info
  INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)
target_compile_features(compile_info
  INTERFACE
    $<BUILD_INTERFACE:cxx_nullptr>
)
set(cxx_lang "$<COMPILE_LANGUAGE:CXX>")
set(debug_cxx_lang "$<AND:$<CONFIG:DEBUG>,${cxx_lang}>")

if(NOT WIN32)
target_compile_options(compile_info INTERFACE
  $<${cxx_lang}:$<BUILD_INTERFACE:-Wall>>
  $<${debug_cxx_lang}:$<BUILD_INTERFACE:-Wunused-parameter>>
)
endif()



#The primary libary. Sources can be added incrementally
add_library(qtvis "")
target_link_libraries(qtvis
  PUBLIC Qt5::OpenGL OpenGL::GL
  PRIVATE compile_info)

#Primary library and demos
add_subdirectory(include)
add_subdirectory(src)

include(GNUInstallDirs)
set(QVIS_INSTALL_INCLUDE_PATH ${CMAKE_INSTALL_INCLUDEDIR}/qtvis)
set(QVIS_PKG_PATH ${CMAKE_INSTALL_LIBDIR}/QtVis/cmake)
set(QVIS_PERMS644 OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ)
set(QVIS_PERMS755 OWNER_READ OWNER_WRITE OWNER_EXECUTE
   GROUP_READ GROUP_EXECUTE  WORLD_READ WORLD_EXECUTE)
install(DIRECTORY include/
        DESTINATION ${QVIS_INSTALL_INCLUDE_PATH}
        FILE_PERMISSIONS ${QVIS_PERMS644}
      DIRECTORY_PERMISSIONS ${QVIS_PERSM755})
install(FILES ${CMAKE_BINARY_DIR}/qtvis_autogen/include/ui_mainwindow.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/qtvis
      PERMISSIONS ${QVIS_PERSM644})
install(TARGETS compile_info EXPORT core)
install(TARGETS qtvis
  EXPORT core
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PERMISSIONS ${QVIS_PERSM644}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/qtvis)
install(EXPORT core
  NAMESPACE QtVis::
DESTINATION ${QVIS_PKG_PATH})


include(CMakePackageConfigHelpers)
configure_package_config_file(QtVisConfig.cmake.in
QtVisConfig.cmake
INSTALL_DESTINATION ${QVIS_PKG_PATH})
write_basic_package_version_file("QtVisConfig0.1.cmake"
COMPATIBILITY SameMajorVersion)
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/QtVisConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/QtVisConfig0.1.cmake
PERMISSIONS ${QVIS_PERSM644}
DESTINATION ${QVIS_PKG_PATH})

#for CUDA
include(CheckLanguage)
check_language(CUDA)
if(CMAKE_CUDA_COMPILER)
  enable_language(CUDA)
  #Autodetect CUDA architecture
  include(${CMAKE_SOURCE_DIR}/cmake_modules/detectCUDAarch.cmake)
  set(cuda_lang "$<COMPILE_LANGUAGE:CUDA>")
  set(debug_cuda_lang "$<AND:$<CONFIG:DEBUG>,${cuda_lang}>")
  if(NOT WIN32)
  target_compile_options(compile_info INTERFACE
    $<${cuda_lang}:$<BUILD_INTERFACE:-Xcompiler=-Wall>>
    $<${debug_cuda_lang}:$<BUILD_INTERFACE:-Xcompiler=-Wunused-parameter>>
  )
endif()
  target_compile_options(compile_info INTERFACE
      $<${cuda_lang}:$<BUILD_INTERFACE:${QVis_CUDA_ARCH}>>
  )

  #CUDA Specific libraries/demos
  #Build a separate qtviscuda library that only needs
  #to be linked into cuda applications
  add_subdirectory(src/cuda)
  #Sample cuda demos linking qtvis and qtviscuda
  add_subdirectory(demos/cuda)
else()
  message(STATUS
  "Could not find CUDA, set CMAKE_CUDA_COMPILER to\n
   full path to nvcc if you think this is an error")
  #Optionally, add path to nvcc to PATH env variable
endif()


#for PThreads
find_package(Threads)
if(CMAKE_USE_PTHREADS_INIT)
  target_link_libraries(qtvis PUBLIC Threads::Threads)
  #C-wrapper library 
  add_subdirectory(src/pthreads)
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
  target_link_libraries(qtvis PUBLIC OpenMP::OpenMP_CXX)
  add_subdirectory(demos/openMP)
endif()

add_subdirectory(demos)
