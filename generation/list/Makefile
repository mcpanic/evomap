all: MapGenome.o MapNode.o main.cpp  
	g++ -g -o evolve main.cpp MapGenome.o MapNode.o -lga 

testGenome: testGenome.cpp MapGenome.o 
	g++ -o gtest testGenome.cpp MapGenome.o

MapGenome.o: MapGenome.cpp
	g++ -g -c -o MapGenome.o MapGenome.cpp 

MapNode.o: MapNode.cpp
	g++ -g -c -o MapNode.o MapNode.cpp

MapGenome.cpp: MapGenome.h MapNode.h

testGenome.cpp: MapGenome.h

MapNode.cpp: MapNode.h

