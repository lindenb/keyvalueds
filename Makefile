.PHONY:all clean
BDB=/home/lindenb/package/db-5.0.21.NC/build_unix
CC=g++ 
CFLAGS=-Wall -I ${BDB}
LDFLAGS= -L${BDB} -ldb -lpthread

all: kvds

kvds : keyvalueds.o
	$(CC) -o $@ $^ $(LDFLAGS)

keyvalueds.o: keyvalueds.cpp keyvalueds.hpp
	$(CC) -o $@ $(CFLAGS) -c $<


clean:
	rm kvds *.o
