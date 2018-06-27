
add_library(demothread pthreadVis.h pthreadVis.cpp)
add_executable(threadDemo threadDemo.cpp)
target_link_libraries(threadDemo demothread ${COMLIBS} Threads::Threads )
if(APPLE)
 target_link_libraries(threadDemo osxbarrier)
endif()
set_target_properties(threadDemo PROPERTIES RUNTIME_OUTPUT_DIRECTORY
  $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
)
