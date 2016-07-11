# Suppress output except warnings
.SILENT:

# Files to compile
OBJS = Net_test.c network.c neuron.c

# Compiler
CC = gcc

# Compiler options
# -w suppresses all warnings
# -g compiles with debug symbols
# -O2 best optimization without increasing executable size
COMPILER_FLAGS = -w -O2 -std=gnu11

# Compiler options for the debug executable
DBG_COMPILER_FLAGS = -g -Wall -Wno-unused-function -std=gnu11

# Headers to include
INCLUDE = 

# Libraries to link
LINKER_FLAGS = -lm

# Executable name
OBJ_NAME = neurotic


# Rules
all : $(OBJS)
	# Create executable
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(INCLUDE) -o $(OBJ_NAME)


debug : $(OBJS)
	# Create executable
	$(CC) $(OBJS) $(DBG_COMPILER_FLAGS) $(LINKER_FLAGS) $(INCLUDE) -o $(OBJ_NAME)

clean : $(OBJ_NAME)
	# Delete executable
	rm $(OBJ_NAME)
