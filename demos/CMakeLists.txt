
add_library(democpu gradientVis.h gradientVis.cpp)
target_link_libraries(democpu PUBLIC inclib Qt5::Core)

add_executable(cpuDemo main.cpp)
target_link_libraries(cpuDemo democpu ${COMLIBS})
set_target_properties(cpuDemo PROPERTIES RUNTIME_OUTPUT_DIRECTORY
  $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
)
