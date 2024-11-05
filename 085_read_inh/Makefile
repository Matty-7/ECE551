CFLAGS= -Wall -Werror -std=gnu++98 -pedantic -ggdb3


test: code.cpp
	g++ $(CFLAGS) -o test code.cpp

run: test
	./test > answer.txt

clean:
	rm -f test *~
