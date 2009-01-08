#include <ga/ga.h>
#include <ga/std_stream.h>
#include "MapGenome.h"


int DICSIZE = 100;

float objective(MapGenome &);

int main(int argc, char* argv[])
{

	// set default parameters

	// Define Genome
	MapGenome genome;

	// Define GA
	GASteadyStateGA ga(genome);
	// remove crossover

	ga.populationSize(10);
  ga.nGenerations(10);
	ga.pMutation(0.2);
	ga.set(gaNpCrossover, 0.0);	

	// Evolve
	ga.evolve();
}

