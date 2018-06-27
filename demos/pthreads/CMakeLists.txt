
add_library(demothread pthreadVis.h pthreadVis.cpp)

target_include_directories(demothread PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

add_executable(threadDemo threadDemo.cpp)
target_link_libraries(threadDemo demothread ${COMLIBS} Threads::Threads )

target_include_directories(threadDemo PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)
if(APPLE)
 target_link_libraries(threadDemo osxbarrier)
endif()
set_target_properties(threadDemo PROPERTIES RUNTIME_OUTPUT_DIRECTORY
  $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
)
