include_directories( ../CircularBuffer )
add_executable(example main.cpp)
target_link_libraries(example CircularBuffer) 
