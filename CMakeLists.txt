cmake_minimum_required (VERSION 2.6)

# Project name and version
project (NeuroticNetwork)
set(NN_MAJOR_VERSION 0)
set(NN_MINOR_VERSION 1)
set(NN_PATCH_VERSION 2)

# Compiler flags
if (CMAKE_COMPILER_IS_GNUCC)
	SET(CMAKE_C_FLAGS "")
endif (CMAKE_COMPILER_IS_GNUCC)

add_subdirectory(src)
