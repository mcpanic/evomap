all: MapGenome.o main.cpp  
	g++ -g -c -o MapGenome.o MapGenome.cpp 
	g++ -g -o evolve main.cpp MapGenome.o -lga 

testGenome: testGenome.cpp MapGenome.o 
	g++ -o gtest testGenome.cpp MapGenome.o

MapGenome.o: MapGenome.cpp
	g++ -g -c -o MapGenome.o MapGenome.cpp 

MapGenome.cpp: MapGenome.h 

MapGenome.h: MapNode.h LinkedList.h Graph.h

testGenome.cpp: MapGenome.h

clean:
	rm -f *.o 
	rm evolve
