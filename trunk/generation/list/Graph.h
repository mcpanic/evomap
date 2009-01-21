#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "LinkedList.h"
#include "MapNode.h"


class DirectedGraph {
	public:
		void addNode(int id);
		void addEdge(int fromid, int toid);
		void deleteNode(int id);
		void deleteNthNode(int n);
		void deleteEdge(int fromid, int toid);
		void deleteRandomEdge();

	private:
		SortedLinkedList<MapNode> nodeList;
};

class UndirectedGraph {
	public:
		void addNode(int id) {
		}
		void addEdge(int fromid, int toid);
		void deleteNode(int id);
		void deleteNthNode(int n);
		void deleteEdge(int fromid, int toid);
		void deleteRandomEdge();

	private:
		SortedLinkedList<MapNode> nodeList;
};



#endif
