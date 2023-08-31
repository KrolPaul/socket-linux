CC=gcc
CXX=g++
CFLAGS=-c -lstdc++ -Wall
LDFLAGS=
VPATH := ../connection ../buffer


SRCS=main.cpp socket.cpp client.cpp transceiver.cpp threadactions.cpp
OBJS := $(SRCS:.cpp=.o)
EXECUTABLE=program1


all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o
