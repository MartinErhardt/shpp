SRCS = $(shell find -name '*.cpp')
OBJS = $(addsuffix .o,$(basename $(SRCS)))

CXX = g++

CXXFLAGS = -Wall -Werror -pedantic -O2

shpp: $(OBJS)
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

clean:
	rm $(OBJS)

.PHONY: clean
