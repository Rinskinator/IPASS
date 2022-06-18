#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
# 
#############################################################################

# source files in this project (main.cpp is automatically assumed)
SOURCES := pca9685.cpp robotHond.cpp

# header files in this project
HEADERS := pca9685.hpp robotHond.hpp

# other places to look for files for this project
SEARCH  := 

SERIAL_PORT_DUE   ?= COM3

# set RELATIVE to the next higher directory 
# and defer to the appropriate Makefile.* there
RELATIVE := ..
include $(RELATIVE)/Makefile.due
