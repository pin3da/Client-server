CC=g++
FLAGS=-std=c++11 -O2 -Wall
LDLIBS=-lzmqpp -lzmq

all: server client

server: server.cc
	$(CC) $(FLAGS) $(LDLIBS) -o server server.cc

client: client.cc
	$(CC) $(FLAGS) $(LDLIBS) -o client client.cc

clean:
	rm -f client server *.o *~
