CC = g++
CFLAGS = -Wall -c
INCLUDES = -I../thirdparty
ARCHIVER = ar
ARCHIVER_FLAGS = -cvq

all: default

default: *.o
	$(ARCHIVER) $(ARCHIVER_FLAGS) ../libs/libUtils.a *.o

*.o:
	$(CC) $(CFLAGS) $(INCLUDES) *.cpp

clean:
	rm -rf *.a *.o
