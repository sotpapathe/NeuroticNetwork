

# Suppress output except warnings
.SILENT:

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

# Headers to include
INCLUDE = 

# Libraries to link
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

Net_test.o : Net_test.c neuron.h network.h
	$(CC) $(CFLAGS) $(LINK) $(INCLUDE) -c Net_test.c

neuron.o : neuron.c neuron.h essentials.h
	$(CC) $(CFLAGS) $(LINK) $(INCLUDE) -c neuron.c

network.o : network.c network.h neuron.h
	$(CC) $(CFLAGS) $(LINK) $(INCLUDE) -c network.c

essentials.o : essentials.c essentials.h
	$(CC) $(CFLAGS) $(LINK) $(INCLUDE) -c essentials.c

clean :
	rm -f $(OBJS) $(PROG)

# End of makefile
