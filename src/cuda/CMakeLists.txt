#A C++ file that needs the cuda.h header, but not the CUDA compiler
target_sources(qtvis
   PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/dataVisCUDA.cpp
)
#New CUDA support doesn't seem to have a way to get cuda include path
#so we guess a solution by looking for include folder include dir of
#nvcc
get_filename_component(VIS_NVCC_PATH ${CMAKE_CUDA_COMPILER} DIRECTORY)
string(REPLACE "bin" "include" VIS_CUDA_INCLUDE ${VIS_NVCC_PATH})
target_include_directories(qtvis
  PUBLIC
  ${VIS_CUDA_INCLUDE}
)

add_library(qtviscuda "")
target_sources(qtviscuda PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/handle_cuda_error.cu
  ${CMAKE_CURRENT_LIST_DIR}/timerGPU.cu
  ${CMAKE_CURRENT_LIST_DIR}/cudaWrapper.cu
)
target_link_libraries(qtviscuda PRIVATE compile_info)
install(TARGETS qtviscuda
  EXPORT core
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PERMISSIONS ${QVIS_PERSM644}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/qtvis)
