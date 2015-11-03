# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/utp/zmq/lib
#export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:/Users/utp/zmq/lib

##CC=g++ -std=c++11 -Wall -L/home/utp/zmq/lib -I/home/utp/zmq/include

ZMQDIR = /home/utp/zmq

CC=g++ -std=c++11 -Wall

LDFLAGS= -lpthread -lzmqpp -lzmq -I$(ZMQDIR)/include -L$(ZMQDIR)/lib

all: server worker recollector

server: server.cc
	$(CC) -o server server.cc $(LDFLAGS)

worker: worker.cc
	$(CC) -o worker worker.cc $(LDFLAGS)

recollector: recollector.cc
	$(CC) -o recollector recollector.cc $(LDFLAGS)
	
clean:
	rm -f server worker recollector

