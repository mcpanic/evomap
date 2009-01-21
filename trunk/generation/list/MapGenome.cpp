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
	for(MapNode* i = nodeList.iterator();nodeList.hasNext(i);i = nodeList.next())
	{
		int nodeid = i->getId();
		if(id == nodeid)
			return false;
		if(id < nodeid)
		{
			nodeList.warp(nodeList.getIterator());
			MapNode newnode(id);
			if(i == nodeList.getIterator().head())
				nodeList.insert(newnode,GAListBASE::HEAD);
			else
				nodeList.insert(newnode,GAListBASE::BEFORE);

			return true;
		}
	}
	// id > all existing node id
	nodeList.tail();
	MapNode newnode(id);
	nodeList.insert(newnode, GAListBASE::TAIL);
	return true;

}

bool MapGenome::insertNode(MapNode* oldnode)
{
	if(oldnode==NULL) {
		printf("unexpected null in MapGenome::insertNode\n");
		exit(0);
		return false;
	}

	int id = oldnode->getId();
	for(MapNode *i = nodeList.iterator(); nodeList.hasNext(i);i = nodeList.next())
	{
		int nodeid = i->getId();
		if(id == nodeid)
			return false;
		if(id < nodeid)
		{
			nodeList.warp(nodeList.getIterator());
			if(i == nodeList.getIterator().head())
				nodeList.insert(*oldnode,GAListBASE::HEAD);
			else
				nodeList.insert(*oldnode,GAListBASE::BEFORE);
			return true;
		}
	}
	nodeList.tail();
	nodeList.insert(*oldnode,GAListBASE::TAIL);

	
	return true;	
}


int MapGenome::getNodeId(MapNode& node)
{
	return *(node.head());
}

// remove all edge toward node 'id'
void MapGenome::purgeEdges(int id)
{
	GAListIter< MapNode >iter(nodeList);
	MapNode *head = iter.head();
	bool start = true;

	for(MapNode* i = head;i && (start || i!=head);i = iter.next())
	{
		start = false;
		GAListIter< int > iter(*i);
		int *head = iter.head();
		bool start = true;
		//for all edges
		for(int *i2 = head; i2 && (start || i2!=head);i2 = iter.next())
		{
			if(*i2 == id && !start)
			{
				i->warp(iter);
				i->destroy();
				break;
			}
			start = false;

		}
	}
}

void MapGenome::renameAllEdges(int id, int newid)
{
	GAListIter< MapNode >iter(nodeList);
	MapNode *head = iter.head();
	bool start = true;

	for(MapNode* i = head;i && (start || i!=head);i = iter.next())
	{
		start = false;
		GAListIter< int > iter(*i);
		int *head = iter.head();
		bool start = true;
		//for all edges
		for(int *i2 = head; i2 && (start || i2!=head);i2 = iter.next())
		{
			if(*i2 == id && !start)
			{
				*i2 = newid;
				break;
			}
			start = false;
		}
	}

}


int MapGenome::addRandomEdge()
{
	int count = 0;
	int size = nodeList.size();

	// select target node
	int target = GARandomInt(0,size-1);
	int targetid;
	int j = 0 ;
	for(MapNode *i = nodeList.iterator(); nodeList.hasNext(i); i = nodeList.next())
	{
		if(j == target)
		{
			targetid = i->getId();
			break;
		}
		j++;
	}

	// select source node and add target edge
	target = GARandomInt(0,size-1);
	j = 0;
	for(MapNode *i = nodeList.iterator();nodeList.hasNext(i); i = nodeList.next())
	{
		if(j == target)
		{
			// same node from/to selected, abort
			if(targetid == i->getId())
				return 0;
			i->addEdge(targetid);
			break;
		}
	}
	
	printf("addRandomEdge\n");

}

int MapGenome::removeRandomEdge()
{
	// select target node
	int target = GARandomInt(0,size-1);
	int targetid;
	int j = 0 ;
	for(MapNode *i = nodeList.iterator(); nodeList.hasNext(i); i = nodeList.next())
	{
		if(j == target)
		{
			targetid = i->getId();
			break;
		}
		j++;
	}


}

int MapGenome::addRandomNode()
{
	printf("addRandomNode\n");

	int count = 0;
	int id = GARandomInt(0,DICSIZE-1);
	int size = nodeList.size();
	if(insertNode(id))
	{
		size++;
		int fromid = GARandomInt(0,size-1);

		// make a random edge	
		GAListIter< MapNode > iter(nodeList);
		MapNode *head = iter.head();
		bool start = true;
		int c = 0;
		for(MapNode *i = head; i && (start || i!=head); i = iter.next())
		{
			start = false;	
			if(c == fromid) {
				i->addEdge(id);
				count ++;
				break;
			}
			c++;
		}
	}

	return count;

}

int MapGenome::removeRandomNode()
{
	printf("removeRandomNode\n");

	int count = 0;
	int size = nodeList.size();
	int target = GARandomInt(0,size-1);

	GAListIter< MapNode > iter(nodeList);
	MapNode *head = iter.head();
	bool start = true;
	int c = 0;
	for(MapNode *i = head; i && (start || i!=head); i = iter.next())
	{
		start = false;	
		if(c == target) {
			//delete this node
			nodeList.warp(iter);
			MapNode* target = nodeList.remove();
			if(target!=NULL)
			{
				int id = target->getId();
				delete target;
				purgeEdges(id); //delete all edge toward this node	
				count ++;
			}
			break;
		}
		c++;
	}

	return count;
}

int MapGenome::renameRandomNode()
{
	printf("renameRandomNode\n");
	int size = nodeList.size();
	int id = GARandomInt(0,size-1);

	GAListIter< MapNode > iter(nodeList);
	MapNode *head = iter.head();
	bool start = true;
	int c = 0;
	for(MapNode *i = head; i && (start || i!=head); i = iter.next())
	{
		start = false;
		if(c == id) {
			//delete this node
			nodeList.warp(iter);
			MapNode* target = nodeList.remove();
			int newid;
			int oldid = target->getId();
			do {
				newid = GARandomInt(0,DICSIZE-1);
				target->setId(newid);
			} while(!insertNode(target));			
			
			renameAllEdges(oldid, newid);
			break;
		}
		c++;
	}

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
	GAListIter< MapNode > iter(genome.nodeList);
	MapNode *head = iter.head();
	bool start = true;
	for(MapNode *i = head; i && (start || i!=head); i = iter.next())
	{
		start = false;		
		GAListIter< MapNode > iter(genome.nodeList);
		MapNode *head = iter.head();
		bool start = true;
		for(MapNode *i2 = head; i2 && (start || i2!=head); i2 = iter.next())
		{
			start = false;
			// flip coin here
			if(GAFlipCoin(INITGRAPHSPARSITY))
				i->addEdge(i2->getId());
		}
	}

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

	// change topic map by: add/remove node or edge
  MapGenome &child=(MapGenome &)g;
	int nMut = 0;

  if(pMut <= 0.0) return 0;
	
	cout << child << endl;

	if(GAFlipCoin(pMut))
		child.MutateNode(pMut);

printf("mutated\n");
	cout << child << endl;

  return nMut;
}

/* mutate node 
 * 1) add
 * 2) remove (remove edges toward it)
 * 3) rename
 * */
int MapGenome::MutateNode(float pMut)
{
	int size = nodeList.size();
	int count = 0;

	// add nodes,
	if(GAFlipCoin(pMut) / 3.0)
	{
		count += addRandomNode();
	}
	// randomly remove a node
	if(size > 0 && GAFlipCoin(pMut / 3.0))
	{
		count += removeRandomNode();
	}

	// randomly rename
	if(size>0 && GAFlipCoin(pMut / 3.0))
	{
		count += renameRandomNode();
	}

	return count;
} 

/* mutate edge
 * 1) add
 * 2) remove
 */
int MapGenome::MutateEdge(float pMut)
{
	
	// add random edge
	// remove random edge
	
	if(GAFlipCoin(pMut * 0.5))
		addRandomEdge();
	if(GAFlipCoin(pMut * 0.5))
		removeRandomEdge();

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
