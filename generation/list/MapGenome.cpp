#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <ga/ga.h>
using namespace std;
#include "MapGenome.h"

extern int DICSIZE;


MapGenome::MapGenome() {
	initializer(Init);
	mutator(Mutate);
	evaluator(Evaluate);
	crossover(Cross);
}

MapGenome::MapGenome(const MapGenome& orig) { 
	copy(orig); 
}

MapGenome::~MapGenome() {
	//nodeList is deleted automatically
}

MapGenome& MapGenome::operator=(const GAGenome& orig){
	if(&orig != this) copy(orig);
	return *this;
}

GAGenome* MapGenome::clone(CloneMethod) const 
{
	return new MapGenome(*this);
}

void MapGenome::copy(const GAGenome& orig) {
	// this copies all of the base genome parts
	GAGenome::copy(orig);
	MapGenome& genome = (MapGenome&)orig;
	nodeList.copy(genome.nodeList);
}

void MapGenome::clear()
{
	while(nodeList.head())
		nodeList.destroy();
}

bool MapGenome::insertNode(int id)
{
	GAListIter< MapNode >iter(nodeList);
	MapNode *head = iter.head();

	bool start = true;
	for(MapNode* i = head;i && (start || i!=head);i = iter.next())
	{
		start = false;
		int nodeid = *(i->head());
		if(id == nodeid)
			return false;
		if(id < nodeid)
		{
			nodeList.warp(iter);
			MapNode newnode;
			newnode.insert(id);
			nodeList.insert(newnode,GAListBASE::BEFORE);
			return true;
		}
	}

	// id > all existing node id
	iter.tail();
	nodeList.warp(iter);
	MapNode newnode;
	newnode.insert(id);
	nodeList.insert(newnode);
	return true;

}

bool MapGenome::insertEdge(int id)
{
	GAListIter< MapNode >iter(nodeList);
	MapNode *head = iter.head();

	bool start = true;
	// check for duplication
	for(MapNode* i = head;i && (start || i!=head);i = iter.next())
	{
		start = false;
		int nodeid = getNodeId(*i);
		if(id == nodeid)
			return false;
	}

	MapNode* ilist = nodeList.tail();
	ilist->insert(id);
}


int MapGenome::getNodeId(MapNode& node)
{
	return *(node.head());
}


/* Initialization:
 * n = rand(maxnodes)
 * while(i<n) 
 *   make a random node, which is not already in the graph
 * edgefreq = GARandomDouble(Max);
 * 
 * for each node, connect edges by probability(flip coin)
 *
 * remove unconnected nodes
 *
 */
void MapGenome::Init(GAGenome &g)
{
	//initialize genome as a random topic map	
	MapGenome &genome = (MapGenome&)g;
	genome.clear();
	int i = 0;
	int maxnodes = GARandomInt(0,MAXINITNODES);
	while(i<maxnodes)
	{
		// make a random node, which is not alredy in the graph 
		int id = GARandomInt(0,DICSIZE-1);
		if(genome.insertNode(id))
			i++;		
	}

	// make random edges
}


/* Mutate:
 * flip coin(0.5): do node mutation and/or edge mutation
 *
 * node mutation (add remove swap)
 *	
 * edge mutation (add remove relink)
 * 
 */
int MapGenome::Mutate(GAGenome&g, float pMut)
{
	// change topic map by: add/remove node or edge
  MapGenome &child=(MapGenome &)g;
	int nMut = 0;

  if(pMut <= 0.0) return 0;


  return nMut;
}

int MapGenome::MutateNode(float pMut)
{
	return 0;
} 

int MapGenome::MutateEdge(float pMut)
{
	return 0;
} 

float MapGenome::Evaluate(GAGenome&g)
{
	/* include human evaluation */
	return 0.0f;
}

/*
float MapGenome::Compare(const GAGenome&g1, const GAGenome&g2)
{
	  MapGenome &sis=(MapGenome &)g1;
	  MapGenome &bro=(MapGenome &)g2;
		int s1 = sis.map.size();
		int s2 = bro.map.size();
		
	  return s1 == s2 ? 0 : (s1 > s2 ? s1 - s2 : s2 - s1);
}
*/

/* Crossover:
 * select k1, k2 from mom and dad
 * reconstruct brother and sister
 *
 */
int MapGenome::Cross(const GAGenome&g1, const GAGenome&g2, GAGenome*g3, GAGenome*g4)
{
	// not to be implemented
	return 0;
}
