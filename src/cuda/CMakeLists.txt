target_sources(qtvis
   PRIVATE
    src/cuda/dataVisCUDA.cpp
)

cuda_add_library(mycudautil handle_cuda_error.cu timerGPU.cu cudaWrapper.cu)
