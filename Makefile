# Makefile 
# CSCI 480
# Assignment 1

# we assume the pic directory locates one level above,
# change PIC_PATH if this is not the case
# PIC_PATH = $(abspath $(CURDIR)/../pic)
PIC_PATH = /usr/local/src/pic

INCLUDE = -I$(PIC_PATH)
LIBRARIES = -L$(PIC_PATH) -framework OpenGL -framework GLUT -lpicio -ljpeg

COMPILER = g++
COMPILERFLAGS = -O3 $(INCLUDE)

PROGRAM = current
SOURCE = $(file).cpp
OBJECT = $(file).o

.cpp.o: 
	$(COMPILER) -c $(COMPILERFLAGS) $<

all: $(PROGRAM)

$(PROGRAM): $(OBJECT)
	$(COMPILER) $(COMPILERFLAGS) -o $(PROGRAM) $(OBJECT) $(LIBRARIES)

clean:
	-rm -rf *.o *~ .*~ $(PROGRAM)
