set(CUDA_TEST_SRC ${CMAKE_SOURCE_DIR}/test/detect_cuda_arch.cu)
set(CUDA_TEST_OUT ${CMAKE_BINARY_DIR}/detect_cuda_arch)
execute_process(COMMAND
  nvcc -Wno-deprecated-gpu-targets -lcuda
  ${CUDA_TEST_SRC} -o ${CUDA_TEST_OUT})
execute_process(COMMAND ${CUDA_TEST_OUT}
                  RESULT_VARIABLE CUDA_RETURN_CODE
                  OUTPUT_VARIABLE ARCH)

  if(${CUDA_RETURN_CODE} EQUAL 0)
    set(CUDA_SUCCESS "TRUE")
  else()
    set(CUDA_SUCCESS "FALSE")
  endif()

  if (${CUDA_SUCCESS})
    message(STATUS "CUDA Architecture: ${ARCH}")
    #Yay! Add this to the cuda compile options
    target_compile_options(compile_info INTERFACE
      $<${cuda_lang}:$<BUILD_INTERFACE:${ARCH}>>
    )
  else()
    message(WARNING "Unable to infer CUDA architecture: ${ARCH}")
  endif()
