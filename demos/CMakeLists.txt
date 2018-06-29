#Add user generated files here and name of executable
add_executable(cpuDemo main.cpp gradientVis.h gradientVis.cpp)

#Link executable to vis library
target_link_libraries(cpuDemo qtvis compile_info)

#Drop demo into top level build folder
set_target_properties(cpuDemo PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
)
