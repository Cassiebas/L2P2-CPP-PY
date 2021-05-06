# A simple Makefile for compiling small projects

# set the compiler
CC := g++

# set the compiler flags
CPPFLAGS := -std=c++17 `pkg-config --cflags --libs opencv` -I /usr/local/include/ -lraspicam_cv -lraspicam

# add header files here
HDRS :=

# add source files here
SRCS := src/main.cpp

# generate names of object files
OBJS := $(SRCS:.cpp=.o)

# name of executable
EXEC := testcv

# default recipe
all: clean $(EXEC)

# recipe for building the final executable
$(EXEC): $(OBJS) $(HDRS) testcv
	$(CC) -o $@ $(OBJS) $(CPPFLAGS)

# recipe for building object files
#$(OBJS): $(@:.o=.c) $(HDRS) Makefile
#	$(CC) -o $@ $(@:.o=.c) -c $(CFLAGS)

# recipe to clean the workspace
clean:
	rm -f $(wildcard *.o) $(wildcard /src *.o) $(wildcard /modules *.o)$(EXEC)