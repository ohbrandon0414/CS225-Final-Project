# Executable names:
EXE = degree

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = graph.o main.o circle.o shape.o vector2.o degree.o line.o landmarkpath.o

# Use the cs225 makefile template:
include cs225/make/cs225.mk
