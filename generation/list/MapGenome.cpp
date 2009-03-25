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
//	compare(Compare);
	
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
					fprintf(stdout,"connection irregular\n");
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

	if(GAFlipCoin(pMut*0.5))
		nMut += child.mutateNode(pMut);
	if(GAFlipCoin(pMut*0.5))
		nMut += child.mutateEdge(pMut);
	

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

	// randomly rename
	if(size < DICSIZE && size>0 && GAFlipCoin(pMut / 6.0))
	{
		count += renameRandomNode();
	}

	// add nodes
	if(size < DICSIZE && GAFlipCoin(pMut*5.0/6.0*0.9))
	{
		count += addRandomNode();
	}

	// randomly remove a node
	if(GAFlipCoin(pMut*5.0/6.0*0.1))
	{
		count += removeRandomNode();
	}

	return count;
} 

/* mutate edge
 * 1) add
 * 2) remove
 */
int MapGenome::mutateEdge(float pMut)
{
	int count = 0;
	// add random edge
	// remove random edge	
	if(GAFlipCoin(pMut * 0.35))
	{
		count += addRandomEdge();
	}
	if(GAFlipCoin(pMut * 0.65))
	{
		count += removeRandomEdge();
	}

	return count;
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

		t->addEdge(f->getId());
		f->addEdge(t->getId());
		//addEdge(t->getId(),f->getId());
			
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
	int n = GARandomInt(0,nodeList.size()-1);
	// set node id to a different one(must be unique)
	int newid;
	do {
		newid = GARandomInt(0, DICSIZE-1);
			
	}while(findNode(newid)!=NULL);
	// rename all edges 

	nodeList.warp(n);
	MapNode *t = nodeList.remove();
	if(t==NULL){
		fprintf(stdout,"removee is null\n");
		return 0;
	}
	renameEdges(t->getId(),newid);
	t->setId(newid);
	nodeList.insert(*t);
	delete t;

	return 1;
}

int MapGenome::addRandomEdge() {

	int size = nodeList.size();
	int f, t;

	if(size <2)
		return 0;

	do {
		f = GARandomInt(0,size-1);
		t = GARandomInt(0,size-1);
	} while(f ==t);

	MapNode* from = nodeList.warp(f);
	MapNode* to = nodeList.warp(t);

	from->addEdge(to->getId());
	to->addEdge(from->getId());


	return 1;
}

int MapGenome::removeRandomEdge() {
	int size = nodeList.size();
	int f, t;

	if(size <=2)
		return 0;

	do {
		f = GARandomInt(0,size-1);
		t = GARandomInt(0,size-1);
	} while(f == t);

	MapNode* from = nodeList.warp(f);
	MapNode* to = nodeList.warp(t);

	from->deleteEdge(to->getId());
	to->deleteEdge(from->getId());
	
	deleteUnconnectedNodes();
// it may not be 1 if the edge already exists
	return 1;
}



float MapGenome::Evaluate(GAGenome&g)
{
	MapGenome& map = (MapGenome&)g;
	if(map.nodeList.size()==0)
		return 0;
	cout << map;
	printf("end\n");
	float value;
	/* include human evaluation */
	cin >> value;
	return value;
}


float MapGenome::Compare(const GAGenome&g1, const GAGenome&g2)
{
	/*
	  MapGenome &sis=(MapGenome &)g1;
	  MapGenome &bro=(MapGenome &)g2;
		int s1 = sis.map.size();
		int s2 = bro.map.size();

	  return s1 == s2 ? 0 : (s1 > s2 ? s1 - s2 : s2 - s1);
	*/
	return GARandomDouble(0.0, 5.0);
}


/* Crossover:
 * select k1, k2 from mom and dad
 * reconstruct brother and sister
 *
 */
int MapGenome::Cross(const GAGenome&p1, const GAGenome&p2, GAGenome*c1, GAGenome*c2)
{
	if(c1 && c2)
	{
		MapGenome& bro = (MapGenome&)*c1;
		MapGenome& sis = (MapGenome&)*c2;
		bro.copy(p1);
		sis.copy(p2);

		if(((MapGenome&)p1).nodeList.size() == 0 || ((MapGenome&)p2).nodeList.size() == 0)
			return 0;
		
		MapNode *bro_arm_root, *sis_arm_root;// roots
		UndirectedGraph *bro_arm = bro.getRandomSubgraph(&bro_arm_root);
		UndirectedGraph *sis_arm = sis.getRandomSubgraph(&sis_arm_root);

		int broid = bro_arm_root->getId();
		int sisid = sis_arm_root->getId();
		int tmpid = DICSIZE; // temporaryu
		bro_arm->renameNode(broid, tmpid);
		sis_arm->renameNode(sisid, tmpid+1);


		bro.subtract(*bro_arm);
		sis.subtract(*sis_arm);

		bro_arm->renameNode(tmpid, broid);
		sis_arm->renameNode(tmpid+1, sisid);


		bro_arm->renameNode(broid, sisid);
		sis_arm->renameNode(sisid, broid);


		bro.combine(*sis_arm);
		sis.combine(*bro_arm);

		delete sis_arm;
		delete bro_arm;

		if(bro.nodeList.size() == 0 || sis.nodeList.size() == 0)
		{
			printf("error, no node\n");
			exit(0);
		}

	
		return 2;
	}

	return 0;
}

UndirectedGraph* MapGenome::getRandomSubgraph(MapNode** root)
{
	// * declare a graph
	// * choose random node as root
	// * from this node, extract and put it in new graph
	// * do it recursively for each outgoing node
	
	int size = nodeList.size();
	UndirectedGraph *newgraph = new UndirectedGraph();
	MapNode *rootNode = nodeList.warp(GARandomInt(0,size-1));  // select random node
	
	MapNode* newroot = newgraph->addNode(rootNode->getId()); //save node

	ListIterator<int> iter(*rootNode);
	for(int* i = iter.start();iter.hasNext(i);i = iter.next())
	{
		if(GAFlipCoin(0.1)) {
			newgraph->addNode(*i);//save node
			newgraph->addEdge(newroot->getId(),*i);// save edge
			_getSubgraph(*i,*newgraph);
		}
	}

	if(newroot->size() == 0)
	{
		//randomly select one adjacent node
		int size = rootNode->size();
		int oid = *rootNode->warp(GARandomInt(0,size-1));
		MapNode* other = findNode(oid);
		newgraph->addNode(oid);
		newgraph->addEdge(newroot->getId(),oid);
		_getSubgraph(oid,*newgraph);
	}

	*root = rootNode; // return value

	return newgraph;
}

void MapGenome::_getSubgraph(int rootid, UndirectedGraph& newgraph)
{
	MapNode *newroot = findNode(rootid);

	ListIterator<int> iter(*newroot);
	for(int* i = iter.start();iter.hasNext(i);i = iter.next())
	{
		if(GAFlipCoin(0.4)) { // selectively save edge and adjacent node
			newgraph.addNode(*i);//save node 
			newgraph.addEdge(newroot->getId(),*i);//save edge
			_getSubgraph(*i,newgraph); 
		}
	}
}
