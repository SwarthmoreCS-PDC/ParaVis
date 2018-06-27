
add_library(democpu gradientVis.h gradientVis.cpp)
add_executable(cpuDemos main.cpp)
target_link_libraries(cpuDemos democpu ${COMLIBS})
set_target_properties(cpuDemos PROPERTIES RUNTIME_OUTPUT_DIRECTORY
  $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
)
