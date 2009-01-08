#include <ga/ga.h>
#include <ga/std_stream.h>
#include <iostream.h>
#include <fstream.h>

#define cout STD_COUT
#define ostream STD_OSTREAM


int DICSIZE = 100;

void initialize(GAGenome&g);
//int mutate(GAGenome&g, float pMut);
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
	GATreeGenome<int> genome;
	genome.evaluator(objective);
	genome.initializer(initialize);
	//genome.mutator(mutate);
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
	GATreeGenome<int> &genome = (GATreeGenome<int>&)g;

// destroy pre-existing tree
	genome.root();
	genome.destroy();

 int depth=2, n=3, count=0;
  genome.insert(count++,GATreeBASE::ROOT);

  for(int i=0; i<depth; i++){
    genome.eldest();
    genome.insert(count++);
    for(int j=0; j<n; j++)
      genome.insert(count++,GATreeBASE::AFTER);
  }

}

/*
int mutate(GAGenome&g, float pMut)
{
	GATreeGenome<int> &genome = (GATreeGenome<int>&)g;
	int nMut = 0;

	double fq = GARandomDouble(0, 0.001);	

	// traverse all the tree in some order(e.g. inorder)
	// check for mutation rate
	// do the mutation ( remove, relink, )



	for(int i = 0; i < genome.width();i++)
	{
			for(int j = 0; j < genome.height(); j++) {
				if(GAFlipCoin(fq)) { 
					genome.gene(i,j,  genome.gene(i,j) ? false : true);
					nMut++;
				}
			}
	}
	return nMut;
}
*/
float objective(GAGenome &g)
{
	GATreeGenome<int> &genome = (GATreeGenome<int>&)g;
	cout << genome << endl << endl;
	cout << "Score: ";
	float score;
	cin >> score;
	return score;
}


template<> 
int GATreeGenome<int>::write(ostream &os) const {

	//write xml
		
	return os.fail() ? 1 : 0;	
}

void writeXMLTree(ostream &os, GATreeGenome<int> &g ) {

	os << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>" << endl;
	os << "<node>" << endl;
  os << "	<label><![CDATA[Stanford CS]]></label>" << endl;
  os << "	<url><![CDATA[http://cs.stanford.edu/]]></url>" << endl;
  os << "	<children>" << endl;
  os << "		<node>" << endl;
  os << "			<label><![CDATA[Courses]]></label>" << endl;
  os << "			<url><![CDATA[http://cs.stanford.edu/courses/]]></url>" endl;
  os << "			<children>" << endl;
	os << "				<node>" << endl;
  os << "				<label><![CDATA[Autumn 2008-2009]]></label>" << endl;
  os << "				<url><![CDATA[http://cs.stanford.edu/courses/schedules/2008-2009.autumn.php]]></url>" << endl;

  os << "<children></children>" << endl;
  os << "</node>" << endl;
  os << "</children>" << endl;
  os << "</node>" << endl;
  os << "</children>" << endl;
  os << "</node>" << endl;


}

_writeXMLTree(ostream &os, 
