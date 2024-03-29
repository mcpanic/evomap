#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "LinkedList.h"
#include "MapNode.h"

/*
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
*/
class UndirectedGraph {
	public:

		MapNode* findNode(int id)
		{
			return nodeList.find(id);
		}

		MapNode* addNode(int id) {
			return nodeList.insert(id);
		}

		bool addEdge(int fromid, int toid) {
			
			if(fromid == toid)
				return false;

			MapNode* from = findNode(fromid);
			MapNode* to = findNode(toid);

			if(from == NULL || to == NULL)
			{
				return false;
			}
				
			from->addEdge(toid);
			to->addEdge(fromid);
			return true;
		}

		void deleteNode(int id)
		{
			MapNode removee(id); 
			nodeList.remove(removee);
			purgeEdges(id);
		}

		void deleteNthNode(int n) {
			MapNode *target = nodeList.warp(n);
			deleteNode(target->getId()); // this part is duplicating search to the target, might be inefficient..
		}

		bool deleteEdge(int fromid, int toid)
		{
			MapNode *from = findNode(fromid);
			MapNode *to = findNode(toid);

			if(from == NULL || to == NULL)
				return false;

			from->deleteEdge(toid);
			to->deleteEdge(fromid);
		}

	protected:
		SortedLinkedList<MapNode> nodeList;
	private:

		// delete all edges involving node with nodeid ( complexity: n * e)
		void purgeEdges(int nodeid,bool delUnconnectedNodes = true) {
			ListIterator< MapNode> iter(nodeList);
			for( MapNode *i = iter.start(); iter.hasNext(i); i = iter.next())
			{
				i->deleteEdge(nodeid);
			}
			if(delUnconnectedNodes)
				deleteUnconnectedNodes();
		}


	public:

	

		void deleteUnconnectedNodes() {
			bool found = true;
			while(found)
			{
				found = false;
				ListIterator< MapNode> iter(nodeList);
				for( MapNode *i = iter.start(); iter.hasNext(i); i = iter.next())
				{
					if(i->size() == 0)
					{
						nodeList.warp(iter);
						nodeList.destroy();
						found = true;
						break;
					}
				}
			}
		}

		void renameEdges(int oldid, int newid) {
			ListIterator< MapNode> iter(nodeList);
			for( MapNode *i = iter.start(); iter.hasNext(i); i = iter.next())
			{
				i->renameEdges(oldid, newid);
			}
					
		}

		bool renameNode(int oldid, int newid)
		{
			MapNode* node = findNode(oldid);
			if(node == NULL)
				return false;
			if(findNode(newid)) // newid must not exist
				return false;
			renameEdges(oldid, newid);
			node->setId(newid);
			return true;
		}

		void subtract(UndirectedGraph& hole)
		{
			ListIterator<MapNode> iter(hole.nodeList);
			for(MapNode *i = iter.start(); iter.hasNext(i); i = iter.next())
			{
				deleteNode(i->getId());
			}
		}

		void combine(UndirectedGraph& addition)
		{
			ListIterator<MapNode> iter(addition.nodeList);
			for(MapNode *i = iter.start(); iter.hasNext(i); i = iter.next())
			{
				// combine node
				MapNode* mynode = findNode(i->getId());
				if(mynode ==NULL)
					mynode = addNode(i->getId()); 

				// combine edges
				ListIterator<int> iter(*i);
				for(int *i = iter.start(); iter.hasNext(i); i = iter.next())
				{
					addEdge(mynode->getId(), *i);
				}

			}
		}

};

#endif
