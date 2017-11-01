CC=g++
CFLAGS=-std=c++11 -pthread
C++FILES=producer_consumer.cpp Semaphore.cpp
HFILES=Semaphore.h


ALL:$(C++FILES) $(HFILES)
	$(CC) $(CFLAGS) *.cpp -o ProComsumer

DEBUG: DEBUGFLAGS=-g -O0
DEBUG: ALL

CLEAN: rm * .o
