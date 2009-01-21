#ifndef __MAPNODE_H__
#define __MAPNODE_H__

#include "LinkedList.h"

class MapNode : public LinkedList<int> {

public:
	// create node with the node id
	MapNode(int id) {
		insert(id);
	}

	int getId() {
		return *head();
	}

	void setId(int id) {
		int *h = head();
		if(h!=NULL)
			*h = id;
	}

	bool addEdge(int targetid)
	{
		ListIterator< int >iter(*this);

		// check for duplication
		for(int* i = iter.start();iter.hasNext(i); i = iter.next())
		{
			if(*i == id)
				return false;
		}

		// actual insertion
		this->tail();
		this->insert(id);

	}

	void deleteEdge(int targetid);

	bool operator==(const MapNode& other) const 
	{
		return getId() == other.getId();
	}
	
	bool operator<(const A& other) const
	{
		return getId() < other.getId();
	}

};

#endif
