#include <ga/ga.h>
#include <ga/std_stream.h>
#include <iostream.h>
#include <fstream.h>

#define cout STD_COUT
#define ostream STD_OSTREAM


int DICSIZE = 100;

void initialize(GAGenome&g);
int mutate(GAGenome&g, float pMut);
float objective(GAGenome &);

char **dictionary;


int main(int argc, char* argv[])
{
	// load dictionary
	std::ifstream fp_in;
	char word[50];
	int size;

	fp_in.open("dictionary.txt", std::ios::in);

	fp_in >> size;
	int s =  size / 10 +1;
	dictionary = (char**)malloc(sizeof(char*) *s);		
	for(int i = 0; i < s; i++)
	{
		dictionary[i] = (char*)malloc(sizeof(char)*50);
	}

	int i = 0; 
	while(!fp_in.eof() && i < size) {
		fp_in.getline(word,50);
		if(fp_in.eof())
			break;
		if(i% 10 == 0)
			strcpy(dictionary[i/10],word);		
		i++;
	}

	size = s;

	DICSIZE = size;

	// Define Genome
	GA2DArrayGenome<bool> genome(DICSIZE,DICSIZE);
	genome.evaluator(objective);
	genome.initializer(initialize);
	genome.mutator(mutate);
//	genome.crossover;

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


void initialize(GAGenome &g)
{
	GA2DArrayGenome<bool> &genome = (GA2DArrayGenome<bool>&)g;
	double fq = GARandomDouble(0, 0.1/(float)DICSIZE);	

	for(int i = 0; i < genome.width();i++)
	{
			for(int j = 0; j < genome.height(); j++) {
				if(GAFlipCoin(fq))
					genome.gene(i,j,true);
				else
					genome.gene(i,j,false);
			}
	}
}

int mutate(GAGenome&g, float pMut)
{
	GA2DArrayGenome<bool> &genome = (GA2DArrayGenome<bool>&)g;
	int nMut = 0;

	double fq = GARandomDouble(0, 0.1/(float)DICSIZE);	

	// edge mutation
	for(int i = 0; i < width(); i++)
	{
		bool exists = false;
		for(int j = 0; j < height(); j++) {
			if(gene(i,j)) {
				exists = true;
				break;	
			}
		}
		if(exists) {
			for(int j = 0; j < height(); j++) {
				if(gene(i,j)) {					
					if(GAFlipCoin(fq)) { 
						genome.gene(i,j,  genome.gene(i,j) ? false : true);
						nMut++;
					}
				}
			}
		}
	}

	for(int i = 0; i < genome.width();i++)
	{
			for(int j = 0; j < genome.height(); j++) {
			}
	}
	return nMut;
}

float objective(GAGenome &g)
{
	GA2DArrayGenome<bool> &genome = (GA2DArrayGenome<bool>&)g;
	cout << genome << endl << endl; 
	cout << "Score: ";
	float score;
	cin >> score;
	return score;
}


template<> 
int GA2DArrayGenome<bool>::write(ostream &os) const {

	for(int i = 0; i < width(); i++)
	{
		bool exists = false;
		for(int j = 0; j < height(); j++) {
			if(gene(i,j)) {
				exists = true;
				break;	
			}
		}
		if(exists) {
			os << dictionary[i] << " - ";
			for(int j = 0; j < height(); j++) {
				if(gene(i,j))
					os << dictionary[j] << " ";
			}
			os << endl;
		}

	}
	return os.fail() ? 1 : 0;	
}
