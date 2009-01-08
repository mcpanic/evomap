class MapGenome : public GA2DArrayGenome<int> {
public:
  
	GADefineIdentity("MapGenome", 201);
	static void Init(GAGenome&);
	static int Mutate(GAGenome&, float);
	static float Evaluate(GAGenome&);
	static int Cross(const GAGenome&, const GAGenome&, GAGenome*, GAGenome*);

public:

	MapGenome() {
		initializer(Init); 
		mutator(Mutate);
		evaluator(Evaluate); 
		crossover(Cross); 
	}

	MapGenome(const MapGenome& orig) { copy(orig); }

	virtual ~MapGenome() {}
	MapGenome& operator=(const GAGenome& orig){
		if(&orig != this) copy(orig);
		return *this;
	}

	virtual GAGenome* clone(CloneMethod) const {return new MapGenome(*this);}

	virtual void copy(const GAGenome& orig) {
		// this copies all of the base genome parts
		MapGenome& g = (MapGenome&)orig;
		GA2DArrayGenome::copy(orig);	
	}

	// Data/member functions specific to this new class
private:
	
};






