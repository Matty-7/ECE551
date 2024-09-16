CC = gcc
CFLAGS = -Wall -g

all: test-power
power.o: power.c
	$(CC) $(CFLAGS) -c power.c

test-power.o: test-power.c
	$(CC) $(CFLAGS) -c test-power.c

test-power: power.o test-power.o
	$(CC) $(CFLAGS) -o test-power power.o test-power.o

clean:
	rm -f *.o test-power
