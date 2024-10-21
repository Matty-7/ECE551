CXX = g++
CXXFLAGS = -Wall -g
TARGET = program
SRCS = code.cpp
OBJS = $(SRCS:.cpp = .o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(TARGET) $(OBJS)
