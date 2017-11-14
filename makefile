CC=g++
CFLAGS=-Wall

nisofbaexe: nisofba.o parser.o
	$(CC) $(CFLAGS) nisofba.o parser.o -o nisofba

nisofba: nisofba.cpp nisofba.h
	$(CC) $(CFLAGS) -c nisofba.cpp

parser: parser.cpp parser.h
	$(CC) $(CFLAGS) -c parser.cpp

.PHONY: clean
clean: 
	rm nisofba.o parser.o
