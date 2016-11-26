# Create executable
add_executable (NeuroticNetwork Net_test.c)

# Source files for library
set(NN_SRC network.c neuron.c essentials.c)
# Create static libraries
add_library(nn STATIC ${NN_SRC})

# Link the libraries
# target_link_libraries (NeuroticNetwork m)
target_link_libraries (NeuroticNetwork nn)

# Set executable output directory
SET_TARGET_PROPERTIES(NeuroticNetwork PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
