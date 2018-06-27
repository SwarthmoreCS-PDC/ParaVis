  cuda_add_library(cudademos
  juliaKernel.h rippleKernel.h userBufferKernel.h
  juliaKernel.cu rippleKernel.cu userBufferKernel.cu
  )

add_executable(cudaDemos cudaDemos.cpp)
target_link_libraries(cudaDemos cudaqt mycudautil cudademos ${COMLIBS})
set_target_properties(cudaDemos PROPERTIES RUNTIME_OUTPUT_DIRECTORY
  $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
)
