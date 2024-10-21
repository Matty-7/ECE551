CXX = g++
CXXFLAGS = -Wall -g
TARGET = code
SRCS = code.cpp
OBJS = $(SRCS:.cpp = .o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

run: $(TARGET)
	./$(TARGET) > answer.txt

clean:
	rm -f $(TARGET) $(OBJS)
