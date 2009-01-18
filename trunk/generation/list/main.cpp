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

	cout << genome;

	// Define GA
	GASteadyStateGA ga(genome);
	ga.populationSize(10);
	ga.nGenerations(10);
	ga.pMutation(0.2);
	ga.set(gaNpCrossover, 0.0);
	// Evolve
	ga.evolve();
}

