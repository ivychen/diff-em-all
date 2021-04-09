CXX=g++
CXXFLAGS = -c -Wall -std=c++2a -O2 -Wno-c++11-extensions

all: main

main: main.o
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean:
	rm *o main
