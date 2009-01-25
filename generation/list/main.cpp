#include <ga/ga.h>
#include <ga/std_stream.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
using namespace std;
#include "MapGenome.h"


int DICSIZE = 100;


int main(int argc, char* argv[])
{

	MapGenome genome;

	MapGenome::Init(genome);


	// Define GA
	GASteadyStateGA ga(genome);
	ga.populationSize(10);
	ga.nGenerations(1000);
	ga.pMutation(1.0);
	ga.set(gaNpCrossover, 0.0);
	// Evolve
	ga.evolve();
}

