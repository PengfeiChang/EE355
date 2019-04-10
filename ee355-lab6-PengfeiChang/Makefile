# contact: Mark Redekopp, David Pritchard

CC = g++
CFLAGS = -g -Wall
LDFLAGS =
SRCS = bmplib.cpp
OBJ = $(SRCS:.cpp=.o)
DEMOSRC = demo.cpp bmplib.cpp
DEMOOBJ = $(DEMOSRC:.cpp=.o)


all: demo

demo: $(DEMOOBJ)
	$(CC) $(CFLAGS) $(DEMOOBJ) -o demo

.cpp.o:
	$(CC) $(CFLAGS) -c $<

bmplib.o : bmplib.h

clean:
	rm -f *.o demo

