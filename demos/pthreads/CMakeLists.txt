
add_library(demothread pthreadVis.h pthreadVis.cpp)
target_link_libraries(demothread PUBLIC inclib)

add_executable(threadDemo threadDemo.cpp)
target_link_libraries(threadDemo
  PRIVATE
     demothread qtvis Threads::Threads
)
if(APPLE)
 target_link_libraries(threadDemo PRIVATE osxbarrier)
endif()
set_target_properties(threadDemo PROPERTIES RUNTIME_OUTPUT_DIRECTORY
  $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
)
