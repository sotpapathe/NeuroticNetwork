

# Suppress output except warnings
.SILENT:
# Needed for extensions such as .cpp
.SUFFIXES: .extension

# Compiler
CC = gcc
# Compiler options
# -w suppresses all warnings
# -g compiles with debug symbols
# -O2 best optimization without increasing executable size
# -Wall show all warnings
CFLAGS = -w -O2 -std=gnu11
# Compiler options for the debug executable
DBG_CFLAGS = -g -Wall -Wno-unused-function -std=gnu11
# Headers
INCLUDE = 
# Libraries
LINK = -lm

# Executable name
PROG = neurotic

# Object files needed
OBJS = Net_test.o neuron.o network.o essentials.o


# Rules ########################################################################

all : $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LINK) $(INCLUDE) -o $(PROG)

debug : $(OBJS)
	$(CC) $(OBJS) $(DBG_CFLAGS) $(LINK) $(INCLUDE) -o $(PROG)

clean :
	rm -f $(OBJS) $(PROG)

# Implicit rule for creating object files
.c.o:
	$(CC) $(CFLAGS) $(LINK) $(INCLUDE) -c $*.c

# Object file dependencies
Net_test.o : neuron.h network.h
neuron.o : neuron.h essentials.h
network.o : network.h neuron.h
essentials.o : essentials.h

# End of makefile
