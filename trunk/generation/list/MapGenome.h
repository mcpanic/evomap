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
	  os << "genome!";
		return os;

	}

private:

	GAList<MapNode> nodeList;
	void clear();
	
	bool insertNode(int id);
	bool insertEdge(int id);
	int getNodeId(MapNode& node);
	int MutateNode(float);
	int MutateEdge(float);

};






