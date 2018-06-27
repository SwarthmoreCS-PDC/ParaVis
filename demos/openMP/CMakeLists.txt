SET(CMAKE_CXX_FLAGS
"${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
add_library(demoopenmp openMPVis.h openMPVis.cpp)
target_include_directories(demoopenmp PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

add_executable(openMPDemo openMPDemo.cpp)
target_link_libraries(openMPDemo demoopenmp ${COMLIBS})
target_include_directories(openMPDemo PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

set_target_properties(openMPDemo PROPERTIES RUNTIME_OUTPUT_DIRECTORY
  $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
)
