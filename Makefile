CC = g++
CFLAGS = -Wall
INCLUDES = -Ithirdparty
DBG_CFLAGS = -g
PROGRAM_NAME = example

all: default

setup:
	mkdir -p libs

deps:
	cd utils; $(MAKE)

debug: setup deps
	$(CC) $(INCLUDES) $(CFLAGS) $(DBG_CFLAGS) *.cpp -o $(PROGRAM_NAME)_dbg -Llibs -lUtils

default: setup deps
	$(CC) $(INCLUDES) -o $(PROGRAM_NAME) *.cpp -Llibs -lUtils

*.o:
	$(CC) $(CFLAGS) *.cpp -L -lutils

clean:
	cd utils; $(MAKE) clean
	rm -rf libs/ *.out *.o $(PROGRAM_NAME) $(PROGRAM_NAME)_dbg

memcheck: debug
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./$(PROGRAM_NAME)_dbg
