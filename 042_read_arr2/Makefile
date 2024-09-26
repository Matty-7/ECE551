CC = gcc
CFLAGS = -Wall -g

TARGET = test

$(TARGET): test.c
	$(CC) $(CFLAGS) -o $(TARGET) test.c

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
