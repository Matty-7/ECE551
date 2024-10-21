CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

TARGET = code

SRC = code.cpp

OUTPUT = answer.txt

all: $(TARGET)
	./$(TARGET) > $(OUTPUT)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) $(OUTPUT)
