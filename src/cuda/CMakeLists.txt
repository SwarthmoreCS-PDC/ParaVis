add_library(cudaqt dataVisCUDA.cpp)
target_link_libraries(cudaqt PUBLIC inclib)

cuda_add_library(mycudautil handle_cuda_error.cu timerGPU.cu cudaWrapper.cu)
