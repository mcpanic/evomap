all: MapGenome.o main.cpp 
	g++ -g -o evolve main.cpp MapGenome.o -lga 

testGenome: testGenome.cpp MapGenome.o 
	g++ -o gtest testGenome.cpp MapGenome.o

MapGenome.o: MapGenome.cpp
	g++ -g -c -o MapGenome.o MapGenome.cpp


MapGenome.cpp: MapGenome.h

testGenome.cpp: MapGenome.h


