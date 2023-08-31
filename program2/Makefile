CC=gcc
CXX=g++
CFLAGS=-c -lstdc++ -Wall
LDFLAGS=
VPATH := ../connection


SRCS=main.cpp socket.cpp server.cpp transceiver.cpp threadactions.cpp
OBJS := $(SRCS:.cpp=.o)
EXECUTABLE=program2


all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o
