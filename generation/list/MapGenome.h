#define MAXINITNODES 6
#include "MapNode.h"

class MapGenome : public GAGenome {
public:

	GADefineIdentity("MapGenome", 201);
	static void Init(GAGenome&);
	static int Mutate(GAGenome&, float);
	static float Evaluate(GAGenome&);
	static int Cross(const GAGenome&, const GAGenome&, GAGenome*, GAGenome*);

public:

	MapGenome();
	MapGenome(const MapGenome& orig);	
	virtual ~MapGenome();

	MapGenome& operator=(const GAGenome& orig);
	virtual GAGenome* clone(CloneMethod) const;
	virtual void copy(const GAGenome& orig);
	virtual int equal(const GAGenome& g) const {
		return 0;
	}

	friend ostream& operator<<(ostream &os, const MapGenome & p) {
		GAListIter< MapNode >iter(p.nodeList);
		MapNode *head = iter.head();
		bool start = true;
		
		for(MapNode* i = head;i && (start || i!=head);i = iter.next())
		{
			start = false;
			os << "node(" << i->getId() << ")" << endl;
			os << "  toward: ";

			GAListIter<int> iter(*i);
			int *head = iter.head();
			bool start = true;
			for(int *i = head; i && (start || i!=head); i = iter.next())
			{
				if(!start) // skip node id
					os << *i << " ";
				start = false;
			}
			os << endl;
		}


		return os;

	}

private:

	GAList<MapNode> nodeList;
	void clear();
	
	bool insertNode(int id);
	int getNodeId(MapNode& node);
	int MutateNode(float);
	int MutateEdge(float);

};






