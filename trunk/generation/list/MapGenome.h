#ifndef __MAPGENOME_H__
#define __MAPGENOME_H__

#define MAXINITNODES 6
#define INITGRAPHSPARSITY 0.4

#include "Graph.h"

class MapGenome : public GAGenome, public UndirectedGraph {
public:

	MapGenome();

	GAGenome* clone(CloneMethod) const 
	{
		return new MapGenome(*this);
	}

	MapGenome(const MapGenome& orig) { 
		copy(orig); 
	}

	MapGenome& operator=(const GAGenome& orig){
		if(&orig != this) copy(orig);
		return *this;
	}


	void copy(const GAGenome& orig) {
		// this copies all of the base genome parts
		GAGenome::copy(orig);
		MapGenome& genome = (MapGenome&)orig;
		nodeList.copy(genome.nodeList);
	}

	virtual int equal(const GAGenome& g) const {
		return 0;
	}

	friend ostream& operator<<(ostream &os, const MapGenome & p) {
		if(p.nodeList.size()==0)
			os << "no node" << endl;
		ListIterator<MapNode> iter(p.nodeList);
		for(MapNode* i = iter.start();iter.hasNext(i);i = iter.next())
		{
			os << "node(" << i->getId() << ")" << endl;
			os << "  toward: ";

			ListIterator<int> iter(*i);
			for(int *i = iter.start(); iter.hasNext(i); i = iter.next())
			{
				//if(!iter.isStart(i)) // skip node id
					os << *i << " ";
			}
			os << endl;
		}

		return os;
	}

public:

	GADefineIdentity("MapGenome", 201);
	static void Init(GAGenome&);
	static int Mutate(GAGenome&, float);
	static float Evaluate(GAGenome&);
	static int Cross(const GAGenome&, const GAGenome&, GAGenome*, GAGenome*);

private:

	void clear();

	int mutateNode(float pMut);
	int mutateEdge(float pMut);
	int addRandomNode();
	int removeRandomNode();
	int renameRandomNode();
	int addRandomEdge();
	int removeRandomEdge();
	void migrateNode(MapNode& target, MapGenome&other); 

	UndirectedGraph* getRandomSubgraph(MapNode** root);
	void _getSubgraph(int, UndirectedGraph&);





};

#endif
