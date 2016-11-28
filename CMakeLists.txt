cmake_minimum_required (VERSION 2.6)

# Project name and version
project (NeuroticNetwork)
set(NN_MAJOR_VERSION 0)
set(NN_MINOR_VERSION 1)
set(NN_PATCH_VERSION 3)

# Compiler flags
if (CMAKE_COMPILER_IS_GNUCC)
	SET(CMAKE_C_FLAGS "")
	SET(CMAKE_C_FLAGS_DEBUG "-g -Wall -Wno-unused-function")
	SET(CMAKE_C_FLAGS_RELEASE "-w -O2")
endif (CMAKE_COMPILER_IS_GNUCC)

############################# DO NOT EDIT THESE ################################

# Write cmake settings to header file
CONFIGURE_FILE(
"${PROJECT_SOURCE_DIR}/src/nn_config.h.in"
"${PROJECT_BINARY_DIR}/nn_config.h"
)
# Include edited header file
INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}")


add_subdirectory(src)
