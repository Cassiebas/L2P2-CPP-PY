CC := g++

CPPFLAGS := -Wall -g

SRCS := $(./*.cpp)

HDRS := $(./*.h)

EXEC := balans

OBJS := $(SRCS:.cpp=.o)

all: clean $(EXEC)

$(EXEC): $(OBJS) $(HDRS) executable
	$(CC) -o $@ $(OBJS) $(CPPFLAGS)

clean:
	rm -f $(wildcard *.o) $(wildcard /src *.o) $(wildcard /modules *.o)$(EXEC)
