#include <ga/ga.h>
#include <ga/std_stream.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
using namespace std;
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


	// Define GA
	GASimpleGA ga(genome);
	ga.set(gaNpopulationSize, 2);	// population size
  ga.set(gaNpCrossover, 0.3);		// probability of crossover
  ga.set(gaNpMutation, 1.0);		// probability of mutation
  ga.set(gaNnGenerations, 10);		// number of generations
 
	//ga.pMutation(1.0);
	//ga.set(gaNpCrossover, 0.4);
	//ga.terminator(GATerminateUponGeneration);
	// Evolve
	ga.evolve();

}

