#include <ga/ga.h>
#include <ga/std_stream.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
using namespace std;
#include "MyGA.h"
#include "MapGenome.h"


int DICSIZE = 100;

GABoolean
GATerminateUponGeneration(GAGeneticAlgorithm & ga){
	  return(ga.generation() < ga.nGenerations() ? gaFalse : gaTrue);
}


int main(int argc, char* argv[])
{
	MapGenome genome;

	MapGenome::Init(genome);

	if(argc == 2)
		DICSIZE = atoi(argv[1]);
	
	// Define GA
	MyGA ga(genome);
	ga.set(gaNpopulationSize, 10);	// population size
  ga.set(gaNpCrossover, 0.1);		// probability of crossover
  ga.set(gaNpMutation, 1.0);		// probability of mutation
  ga.set(gaNnGenerations, 100);		// number of generations
 
	// Evolve
	ga.evolve();
	printf("finishing\n");

}

