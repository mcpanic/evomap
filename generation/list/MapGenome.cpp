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

void MapGenome::clear()
{
	while(nodeList.head())
		nodeList.destroy();
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
	int maxnodes = GARandomInt(2,MAXINITNODES);
	while(i<maxnodes)
	{
		// make a random node, which is not alredy in the graph 
		int id = GARandomInt(0,DICSIZE-1);
		if(genome.addNode(id))
			i++;		
	}
	
	// make random edges
	ListIterator<MapNode> iter(genome.nodeList);
	for( MapNode *i = iter.start(); iter.hasNext(i); i = iter.next())
	{
		ListIterator<MapNode>iter2(genome.nodeList);
		for(MapNode *j = iter2.start(); iter2.hasNext(j); j = iter2.next())
		{
			if(i!=j && GAFlipCoin(INITGRAPHSPARSITY))
			{
				if(i->addEdge(j->getId()) ^	j->addEdge(i->getId()))
					fprintf(stderr,"connection irregular\n");
			}
		}
	}

	//remove nodes with no edges
	genome.deleteUnconnectedNodes();
	

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
  MapGenome &child = (MapGenome&)g;
	int nMut = 0;

  if(pMut <= 0.0) return 0;
	
	cout << child << endl;

	if(GAFlipCoin(pMut))
		child.mutateNode(pMut);
	cout << child << endl;

  return nMut;
}

/* mutate node 
 * 1) add
 * 2) remove (remove edges toward it)
 * 3) rename
 * */
int MapGenome::mutateNode(float pMut)
{
	int size = nodeList.size();
	int count = 0;

	// add nodes
	if(GAFlipCoin(pMut) / 3.0)
	{
		count += addRandomNode();
	}

	// randomly remove a node
	if(GAFlipCoin(pMut / 3.0))
	{
		count += removeRandomNode();
	}

	// randomly rename
	if(size>0 && GAFlipCoin(pMut / 3.0))
	{
		//count += renameRandomNode();
	}

	return count;
} 

/* mutate edge
 * 1) add
 * 2) remove
 */
int MapGenome::mutateEdge(float pMut)
{
	
	// add random edge
	// remove random edge	
	if(GAFlipCoin(pMut * 0.5))
		addRandomEdge();
	if(GAFlipCoin(pMut * 0.5))
		removeRandomEdge();

	return 0;
} 

int MapGenome::addRandomNode() {
	// make a node with random id
	MapNode* f;
	int newid;
	int count  = 0;

	bool more = true;

	while(more)
	{
		more = false;
		int size = nodeList.size();
		do{
			newid = GARandomInt(0, DICSIZE-1);
		}
		while((f = addNode(newid))==NULL);
	
		count ++;

		// we need at least two nodes
		if(nodeList.size()<=1)
		{
			more = true;
			continue;
		}

		// make an edge toward the created node	
		MapNode* t;

		do {
			t = nodeList.warp(GARandomInt(0,nodeList.size()-1));
			
		}	while(t->getId()==f->getId());

		addEdge(t->getId(),f->getId());
		
		
	}
	

	return count;
}

int MapGenome::removeRandomNode() {
	if(nodeList.size()<=2)
		return 0;

	deleteNthNode(GARandomInt(0,nodeList.size()-1));	
	// choose a random node, and delete
	return 0;
}

int MapGenome::renameRandomNode() {
	//choose a random node
			

	return 0;
}

int MapGenome::addRandomEdge() {
	
	return 0;
}

int MapGenome::removeRandomEdge() {
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
