SET(CMAKE_CXX_FLAGS
"${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
add_library(demoopenmp openMPVis.h openMPVis.cpp)
add_executable(openMPDemo openMPDemo.cpp)
target_link_libraries(openMPDemo demoopenmp ${COMLIBS})
set_target_properties(openMPDemo PROPERTIES RUNTIME_OUTPUT_DIRECTORY
  $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
)
