
add_library(democpu gradientVis.h gradientVis.cpp)
target_include_directories(democpu PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

add_executable(cpuDemo main.cpp)
target_include_directories(cpuDemo PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

target_link_libraries(cpuDemo democpu ${COMLIBS})
set_target_properties(cpuDemo PROPERTIES RUNTIME_OUTPUT_DIRECTORY
  $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
)
