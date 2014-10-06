CC=g++
FLAGS=-std=c++11 -O2 -Wall
#LDLIBS=-lzmqpp -lzmq

all: generator multiply

generator: generator.cc
	$(CC) $(FLAGS) $(LDLIBS) -o generator generator.cc

multiply: multiply.cc
	$(CC) $(FLAGS) $(LDLIBS) -o multiply multiply.cc

clean:
	rm -f multiply generator
