CC=g++

CFLAGS=-Wall -pthread  --std=c++14 -g

all: map.o test_map.o
	g++ $(CFLAGS) map.o test_map.o -o map

map.o: map.cpp
	g++ $(CFLAGS) -c map.cpp

test_map.o: test_map.cpp
	g++ $(CFLAGS) -c test_map.cpp

clean:
	rm -rf map.o test_map.o map
