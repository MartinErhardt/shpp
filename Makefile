SRCS = $(shell find -name '*.cpp')
OBJS = $(addsuffix .o,$(basename $(SRCS)))

CXX = g++

CXXFLAGS = -std=c++11 -Wall -Werror -O2 -I src/inc

shpp: $(OBJS)
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

clean:
	rm $(OBJS)

.PHONY: clean
