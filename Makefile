CC = g++
DEBUG = -g -O0 -pedantic-errors
CFLAGS = -c -Wall -std=c++11 $(DEBUG)
LFLAGS = -Wall $(DEBUG)

all:driver btree.o

driver:driver.o btree.o
	$(CC) $(LFLAGS) -o driver driver.o btree.o

btree.o:btree.cpp btree.h
	$(CC) $(CFLAGS) btree.cpp

driver.o:driver.cpp
	$(CC) $(CFLAGS) driver.cpp

.PHONY:
	clean

clean:
	rm -f *.o
	rm -f driver


