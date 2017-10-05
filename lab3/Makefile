CC=g++
CFLAGS=-std=c++11 -pthread
CFILES=mutex.cpp Semaphore.cpp
HFILES=Semaphore.h


ALL:$(CFILES) $(HFILES)
	$(CC) $(CFLAGS) *.cpp -o mutexLab3

DEBUG: DEBUGFLAGS = -DDEBUG
DEBUG: ALL

CLEAN:
	rm *.o
