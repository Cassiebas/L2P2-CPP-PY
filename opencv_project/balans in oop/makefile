CC := g++

CPPFLAGS := -Wall -g

SRCS := $(wildcard ./*.cpp)

HDRS := $(wildcard ./*.h)

EXEC := balans

OBJS := $(SRCS:.cpp=.o)

all: clean $(EXEC)

$(EXEC): $(OBJS) $(HDRS)
	$(CC) -o $@ $(OBJS) $(CPPFLAGS)

clean:
	rm -f $(wildcard *.o) $(wildcard /src *.o) $(wildcard /modules *.o)$(EXEC)
