add_library(shapes sphere.cpp square.cpp cylinder.cpp matrixstack.cpp)
target_link_libraries(shapes PUBLIC inclib Qt5::Core)
