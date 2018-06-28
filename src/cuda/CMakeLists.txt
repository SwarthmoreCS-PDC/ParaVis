target_sources(qtvis
   PRIVATE
    src/cuda/dataVisCUDA.cpp
)
target_include_directories(qtvis
  PUBLIC
  ${CUDA_TOOLKIT_INCLUDE}
)

cuda_add_library(mycudautil handle_cuda_error.cu timerGPU.cu cudaWrapper.cu)
