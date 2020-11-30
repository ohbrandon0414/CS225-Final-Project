# Executable names:
EXE = bfs

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = graph.o main.o degree.o bfs.o

# Use the cs225 makefile template:
include cs225/make/cs225.mk
