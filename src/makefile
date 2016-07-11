# Neurotic Network makefile ####################################################

# Suppress output except warnings
.SILENT:

# Object files needed
OBJS = Net_test.o neuron.o network.o essentials.o
# Source files needed
SRCS = Net_test.c neuron.c network.c essentials.c

include ../makefile.common

# Rules ########################################################################

all : $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LINK) $(INCLUDE) -o $(PROG)

debug : $(OBJS)
	$(CC) $(OBJS) $(DBG_CFLAGS) $(LINK) $(INCLUDE) -o $(PROG)

clean :
	rm -f $(OBJS) $(PROG)

# Object file dependencies
depend:
	makedepend -- $(CFLAGS) -- $(SRCS)

# End of makefile
