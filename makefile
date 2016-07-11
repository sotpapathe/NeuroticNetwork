# Neurotic Network main makefile ###############################################
.SILENT:

include makefile.common

all:
	cd ./src ; make
	mv ./src/$(PROG) .

debug:
	cd ./src ; make debug
	mv ./src/$(PROG) .

clean:
	cd ./src ; make clean
	rm -f $(PROG)

# End of makefile
