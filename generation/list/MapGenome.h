
class MapGenome : public GAListGenome< GAList<int> > {
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


	// Data/member functions specific to this new class
private:

};






