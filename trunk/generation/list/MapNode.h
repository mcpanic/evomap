class MapNode : public GAList<int> {

public:
	// create node with the node id
	MapNode(int id);

	int getId();
	void setId(int id);
	bool addEdge(int id);
	

};


