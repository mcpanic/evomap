#include <ga/ga.h>
#include "MapGenome.h"

extern int DICSIZE;


void MapGenome::Init(GAGenome &g)
{
	//initialize genome as a random topic map	
	MapGenome &genome = (MapGenome&)g;
	//destroy any pre-existing nodes
	genome.reset();

	/// random frequency for nodes and edges
	double nfq = GARandomDouble();
	double efq = GARandomDouble();

	while(nfq == 0.0 || efq == 0.0)
	{
		nfq = GARandomDouble();
		efq = GARandomDouble();
	}

	GAList< GAList<int> > &map = genome.map;


	for(int i = 0; i < DICSIZE; i++)
	{
		if(GAFlipCoin(nfq)) 
			genome.insertNode(i);
	}


	// connect edges
	GAListIter< GAList<int> >iter(map);
	GAList<int>*head = iter.head();

	bool start = true;
	for(GAList<int>* i = head;i && (start || i!=head);i = iter.next())
	{
		start = false;
		GAListIter<int> iter2(*i);
		int *head = iter2.head();
		
		bool start = true;
		for(int *j = head; j && (start || j!=head); j = iter2.next())
		{
			start = false;
			if(GAFlipCoin(efq))
				i->insert(*j);
		}
	}
}

int MapGenome::Mutate(GAGenome&g, float pMut)
{
	// change topic map by: add/remove node or edge
  MapGenome &child=(MapGenome &)g;
	GAList< GAList<int> > &map = child.map; 
	int nMut = 0;

  if(pMut <= 0.0) return 0;

	nMut += child.MutateNode(pMut);

  return nMut;
}

int MapGenome::MutateNode(float pMut)
{
	float pIns = pMut / 3.0;
	float pDel = pMut / 3.0;
	float pMod = pMut / 3.0;
	int nMut = 0;

	// for all nodes, insert/delete/change		
	GAListIter< GAList<int> >iter(map);
	GAList<int>*head = iter.head();

	bool ok = false;
	while(!ok)
	{
		int pos = GARandomInt(0,DICSIZE-1);
		// find appropriate place
		GAListIter< GAList<int> >iter(map);
		GAList<int>*head = iter.head();
		bool start = true;
		for(GAList<int>* j = head; j && (start || j!=head);j = iter.next())
		{
			GAList<int> *next = iter.next();iter.prev();
			if(next == head)	{
				if(*(j->head()) == pos)
					break;
				if(*(j->head())< pos && pos < DICSIZE)
				{
					ok = true;
					map.warp(iter);
					map.insert(pos);
					nMut ++;
					break;
				}
			}
			else {
				if(*(j->head()) == pos || *(next->head()) == pos)
					break;
				if(*(j->head())< pos && pos < *(next->head()))
				{
					ok = true;
					map.warp(iter);
					map.insert(pos);
					nMut ++;
					break;
				}

			}					
		}
	}


	head = iter.head();
	bool start = true;
	for(GAList<int>* i = head;i && (start || i!=head);i = iter.next())
	{
		start = false;

		/* delete */
		if(GAFlipCoin(pDel))
		{
			map.warp(iter);
			GAList<int>* del = map.remove();
			if(del!=NULL) {
				delete del;
				nMut ++;
			}
		}

		if(GAFlipCoin(pMod)) // delete and insert, keeping nodes
		{
			map.warp(iter);
			GAList<int>* del = map.remove();

			if(del!=NULL)
			{
				bool ok = false;
				while(!ok)
				{
					int pos = GARandomInt(0,DICSIZE-1);
					// find appropriate place
					GAListIter< GAList<int> >iter(map);		
					GAList<int>*head = iter.head();
					bool start = true;
					for(GAList<int>* j = head; j && (start || j!=head);j = iter.next())
					{
						GAList<int> *next = iter.next();iter.prev();
						if(next == head)	{
							if(*(j->head()) == pos)
								break;
							if(*(j->head())< pos && pos < DICSIZE)
							{
								ok = true;
								map.warp(iter);
								map.insert(*del);
								nMut++;
								break;
							}
						}
						else {
							if(*(j->head()) == pos || *(next->head()) == pos)
								break;
							if(*(j->head())< pos && pos < *(next->head()))
							{
								ok = true;
								map.warp(iter);
								map.insert(*del);
								nMut++;
								break;
							}

						}					
					}
				}
				delete del;
			}
		}
	}
	
	return nMut;
} 

void MapGenome::MutateEdge()
{
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

int MapGenome::Cross(const GAGenome&g1, const GAGenome&g2, GAGenome*g3, GAGenome*g4)
{
	// not to be implemented
	return 0;
}



