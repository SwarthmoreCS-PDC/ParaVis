  cuda_add_library(cudademos
  juliaKernel.h rippleKernel.h userBufferKernel.h
  juliaKernel.cu rippleKernel.cu userBufferKernel.cu
  )

add_executable(cudaDemo cudaDemo.cpp)
target_include_directories(cudaDemo PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

target_link_libraries(cudaDemo cudaqt mycudautil cudademos ${COMLIBS})
set_target_properties(cudaDemo PROPERTIES RUNTIME_OUTPUT_DIRECTORY
  $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
)
