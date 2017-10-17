CC=g++
CFLAGS=-std=c++11 -pthread
CFILES=reuse_barrier.cpp Semaphore.cpp
HFILES=Semaphore.h


ALL:$(CFILES) $(HFILES)
	$(CC) $(CFLAGS) *.cpp -o barrierLab4

DEBUG: DEBUGFLAGS = -g -O0
DEBUG: ALL

CLEAN:
	rm *.o
