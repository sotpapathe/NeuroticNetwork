# Create executable
add_executable (NeuroticNetwork Net_test.c)

# Source files for library
set(NN_SRC essentials.c neuron.c network.c)
# Create static libraries
add_library(nn STATIC ${NN_SRC})
if (CMAKE_COMPILER_IS_GNUCC)
	target_link_libraries (nn m)
endif (CMAKE_COMPILER_IS_GNUCC)

# Link the libraries
target_link_libraries (NeuroticNetwork nn)

# Set executable output directory
SET_TARGET_PROPERTIES(NeuroticNetwork PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
