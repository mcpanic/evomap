#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <ga/ga.h>

#define WORDMAXLEN 50
using namespace std;

typedef unsigned int Word;
char **dictionary = NULL;
int DICSIZE = 0;


class Topic {
public:
	Topic(Word w) { _word = w; }
	Topic(const Topic & p) { _word = p._word; }
	Topic & operator=(const Topic &p) { _word = p._word; return *this; }
	~Topic() {}

	Word word() const { return _word; }
	Word word(Word val) { return _word = val; }

	friend ostream & operator<<(ostream & os, const Topic & p){
	os << "[" << p._word << "]";
	return os;
	}

	protected:
	Word _word;
};


void loadDic();

float objective(GAGenome &);
void TreeInitializer(GAGenome &);
int TreeMutator(GAGenome &, float);

void WriteNode(ostream & os, GANode<Topic> * n);


int main(int argc, char **argv)
{
	// load dictionary
    loadDic();
	cout.flush();

/*      See if we've been given a seed to use (for testing purposes).  When you
 *      specify a random seed, the evolution will be exactly the same each time
 *      you use that seed number.


    unsigned int seed = 0;
    for(int ii=1; ii<argc; ii++) {
        if(strcmp(argv[ii++],"seed") == 0) {
            seed = atoi(argv[ii]);
        }
    }
*/

    GATreeGenome<Topic> genome(objective);
    genome.initializer(TreeInitializer);
    genome.crossover(GATreeGenome<Topic>::OnePointCrossover);

    genome.mutator(TreeMutator);
    GAPopulation pop(genome, 50);

    GASteadyStateGA ga(genome);
    ga.nGenerations(10);
    ga.population(pop);

    cout << "initializing...";
    ga.initialize(seed);
    cout << "evolving for " << ga.nGenerations() << " generations...";

    while(!ga.done()){
        ga.step();
        cout << ".";
        cout.flush();
    }
    cout << "\n";

    genome = ga.statistics().bestIndividual();
    cout << "the ga generated a tree with " << genome.size();
    cout << " nodes, " << genome.depth() << " levels deep.\n";
    cout << genome;

    return 0;
}



float objective(GAGenome & c) {
    GATreeGenome<Topic> & chrom = (GATreeGenome<Topic> &)c;
    return chrom.size();
}

/* ----------------------------------------------------------------------------
  This initializer creates a tree of random size (within limits).  The maximum
number of children any node can have is limited, so is the maximum depth of
the tree.  We do it recursively.  Each point that is inserted into the tree
has random contents.
  The initializer must first destroy any pre-existing tree or else we have a
memory leak (the initializer may be called more than once - for example when
you re-run the GA).
---------------------------------------------------------------------------- */
const int MAX_DEPTH = 3;
const int MAX_CHILDREN = 3;

void DoChild(GATreeGenome<Topic> & tree, int depth) {
	if(depth >= MAX_DEPTH) return;
		int n = GARandomInt(0,MAX_CHILDREN);	// maximum of 5 children

    Topic t(GARandomInt(0,DICSIZE-1));
    tree.insert(t,GATreeBASE::BELOW);

    for(int i=0; i<n; i++)
        DoChild(tree, depth+1);

    tree.parent();		// move the iterator up one level
}

void TreeInitializer(GAGenome & c) {
    GATreeGenome<Topic> &tree=(GATreeGenome<Topic> &)c;

    // destroy any pre-existing tree
    tree.root();
    tree.destroy();

    // create a root node with coordinates 0,0,0, then do the rest.
    Topic p(GARandomInt(0,DICSIZE-1));
    tree.insert(p,GATreeBASE::ROOT);
    int n = GARandomInt(0,MAX_CHILDREN);	// maximum of 5 children
    for(int i=0; i<n; i++)
        DoChild(tree, 0);
}


int TreeMutator(GAGenome &c, float pMut)
{

    GATreeGenome<Topic>::SwapSubtreeMutator(c, pMut * 0.33);
    GATreeGenome<Topic>::SwapNodeMutator(c, pMut * 0.33);
    GATreeGenome<Topic>::DestructiveMutator(c, pMut*0.33);

}


/* ----------------------------------------------------------------------------
   This is a specialization of the write method for the TreeGenome class.  The
default write method prints out pointers to the nodes.  Here we print the
contents of the nodes.
   This is a recursive implementation (yuk) but it gets the job done.  Beware
that it could crash your machine if your stack is limited and your trees get
very big.
---------------------------------------------------------------------------- */
void WriteNode(ostream & os, GANode<Topic> * n) {
	if(!n) return;
		GANodeBASE * node = (GANodeBASE *)n;

    os.width(10);
    os << ((GANode<Topic> *)node)->contents << " ";
    os.width(10);
    if(node->parent) os << ((GANode<Topic> *)node->parent)->contents << " ";
    else os << "." << " ";
    os.width(10);
    if(node->child) os << ((GANode<Topic> *)node->child)->contents << " ";
    else os << "." << " ";
    os.width(10);
    if(node->next) os << ((GANode<Topic> *)node->next)->contents << " ";
    else os << "." << " ";
    os.width(10);
    if(node->prev) os << ((GANode<Topic> *)node->prev)->contents << "\n";
    else os << ".\n";
    WriteNode(os, (GANode<Topic> *)node->child);

    for(GANodeBASE * tmp=node->next; tmp && tmp != node; tmp=tmp->next){
    os.width(10);
    os << ((GANode<Topic> *)tmp)->contents << " ";
    os.width(10);
    else os << "." << " ";
    if(tmp->parent) os << ((GANode<Topic> *)tmp->parent)->contents << " ";
    os.width(10);
    if(tmp->child) os << ((GANode<Topic> *)tmp->child)->contents << " ";
    else os << "." << " ";
    os.width(10);
    if(tmp->next) os << ((GANode<Topic> *)tmp->next)->contents << " ";
    else os << "." << " ";
    os.width(10);
    if(tmp->prev) os << ((GANode<Topic> *)tmp->prev)->contents << "\n";
    else os << ".\n";
    WriteNode(os, (GANode<Topic> *)tmp->child);
  }
}

template<> int GATreeGenome<Topic>::write(ostream & os) const {
    os << "      node     parent      child       next       prev\n";
    WriteNode(os, (GANode<Topic> *)rt);
    return os.fail() ? 1 : 0;
}

void loadDic()
{
	std::ifstream fp_in;
	char word[WORDMAXLEN];
	int size;

	fp_in.open("dictionary.txt", std::ios::in);

	fp_in >> size;
	int s =  size / 10 +1;
	dictionary = (char**)malloc(sizeof(char*) *s);
	for(int i = 0; i < s; i++)
	{
		dictionary[i] = (char*)malloc(sizeof(char)*WORDMAXLEN);
	}

	int i = 0;
	while(!fp_in.eof() && i < size) {
		fp_in.getline(word,WORDMAXLEN);
		if(fp_in.eof())
			break;
		if(i% 10 == 0)
			strcpy(dictionary[i/10],word);
		i++;
	}

	size = s;
	DICSIZE = size;
}
