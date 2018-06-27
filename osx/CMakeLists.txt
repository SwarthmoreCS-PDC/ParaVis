add_library(osxbarrier pthread_barrier.c)
target_link_libraries(osxbarrier PUBLIC inclib)
