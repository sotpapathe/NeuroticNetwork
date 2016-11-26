cmake_minimum_required (VERSION 2.6)
project (NeuroticNetwork)


include_directories ("${PROJECT_SOURCE_DIR}/src")
add_subdirectory(src)

add_executable (NeuroticNetwork src/Net_test.c)
target_link_libraries (NeuroticNetwork src1)
target_link_libraries (NeuroticNetwork src2)
target_link_libraries (NeuroticNetwork src3)