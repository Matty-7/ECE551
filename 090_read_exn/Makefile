CFLAGS= -Wall -Werror -std=gnu++98 -pedantic -ggdb3


test: code.cpp
	g++ $(CFLAGS) -o test code.cpp > answer.txt 2>&1


clean:
	rm -f test *~
