#define MAXINITNODES 6

class MapGenome : public GAListGenome< MapNode > {
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
	virtual int equal(const GAGenome& g) const;
	

	/* insert with id id
	 * return: true on success, false if fail(id already exist)
	 */
	bool insertNode(int id);
	bool insertEdge(int id);
	void reset();
	static int getNodeId(GAList<int>& list);

	int MutateNode(float);
	int MutateEdge(float);

	friend ostream& operator<<(ostream &os, const MapGenome & p) {
	  os << "genome!";
		return os;

	}


private:

};






