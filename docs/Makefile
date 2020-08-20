# set SHELL to bash
SHELL := /bin/bash

all: documentation

documentation: 			## Build doxygen documentation
	pushd ..; doxygen docs/doxygen.config; popd

cleandocs:			## Remove documentation outputs
	$(RM) -r docs/html
