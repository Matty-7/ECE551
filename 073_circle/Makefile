CXX = g++
CXXFLAGS = -Wall -Werror -pedantic -std=c++98

all: circles

circles: main.o circle.o point.o
	$(CXX) $(CXXFLAGS) -o circles main.o circle.o point.o

main.o: main.cpp circle.hpp point.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

circle.o: circle.cpp circle.hpp point.hpp
	$(CXX) $(CXXFLAGS) -c circle.cpp

point.o: point.cpp point.hpp
	$(CXX) $(CXXFLAGS) -c point.cpp

clean:
	rm -f *.o circles
