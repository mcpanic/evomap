#ifndef __MAPNODE_H__
#define __MAPNODE_H__

#include "LinkedList.h"

class MapNode : public LinkedList<int> {

public:
	// create node with the node id
	MapNode(int id) {
		nodeId = id;
	}

	int getId() const {
		return nodeId;
	}

	void setId(int id) {
		nodeId = id;
	}

	bool addEdge(int targetid)
	{
		ListIterator< int >iter(*this);

		// check for duplication
		for(int* i = iter.start();iter.hasNext(i); i = iter.next())
		{
			if(*i == targetid)
				return false;
		}

		// actual insertion
		this->tail();
		this->insert(targetid);
	}

	bool deleteEdge(int targetid) {
		return remove(targetid);
	}

	bool operator==(const MapNode& other) const 
	{
		return getId() == other.getId();
	}
	
	bool operator<(const MapNode& other) const
	{
		return getId() < other.getId();
	}
	
	private:
		int nodeId;

};

#endif
