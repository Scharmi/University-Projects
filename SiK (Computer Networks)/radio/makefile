CC=g++
CFLAGS=-Wall -std=c++20 -g
BOOST=-lboost_program_options

all: sikradio-sender sikradio-receiver

sikradio-receiver.o: sikradio-receiver.cpp
	$(CC) $(CFLAGS) -c sikradio-receiver.cpp
sikradio-sender.o: sikradio-sender.cpp
	$(CC) $(CFLAGS) -c sikradio-sender.cpp

communication.o: communication.cpp communication.hpp
	$(CC) $(CFLAGS) -c communication.cpp
buffer.o: buffer.cpp buffer.hpp
	$(CC) $(CFLAGS) -c buffer.cpp
safe_fifo.o: safe_fifo.cpp safe_fifo.hpp
	$(CC) $(CFLAGS) -c safe_fifo.cpp
safe_set.o: safe_set.cpp safe_set.hpp
	$(CC) $(CFLAGS) -c safe_set.cpp

sikradio-sender: communication.o safe_fifo.o safe_set.o sikradio-sender.o  err.hpp
	$(CC) $(CFLAGS) sikradio-sender.o communication.o safe_set.o safe_fifo.o -o sikradio-sender $(BOOST)
sikradio-receiver: communication.o buffer.o sikradio-receiver.o err.hpp
	$(CC) $(CFLAGS) sikradio-receiver.o buffer.o communication.o -o sikradio-receiver $(BOOST) -lpthread

clean:
	rm *.o sikradio-sender sikradio-receiver